#pragma once

/*
 * Tracks the memory on the stack in bytes relativly acurate. It does so by storing the stack pointer
 * at different points and Printting the difference by subtracting the 2 points(pointers). The stack grows
 * backwards so we have to subtract the (first pointer - the last) to get a positive number.
 * The function bodies are only compiled in DEBUG_MODE.
 * It is platform and compiler specific so it may not be acurate in every case.
 * The stack pointer dosnt grow whithin a function(or at least a small to medium one) as soon as function
 * is called the stack pointer grows as much as it will whithin the function. Which also means that if you
 * want to track a specific function you cant start tracking in the function. It needs to start
 * outside the function.
 * Currently it is controlled by creating a global object.
 * If the tracker is created before the main function its going to start with value of around -80 bytes,
 * because of the stack pointer behaviour.
 * Since it uses a std::stack<void*> to store the different points it uses the heap(580 bytes by default
 * from the tests and potentionally grows like a vector 2x the size each time it needs to grow).
 */

#ifdef DEBUG_MODE
#include <project_definitions.h>
#include <debug_logger_component.h>
#include <stack>

#endif /* DEBUG_MODE */

/**
 * @file StackMemoryTracker.h
 * @brief Stack memory tracking utility for debugging purposes.
 *
 * This class provides a way to track the stack memory usage during program execution.
 * It records stack pointers at different points in the code and calculates the size of
 * the stack memory used between those points.
 *
 * The class only operates in `DEBUG_MODE`, and its operations are bypassed in release mode.
 *
 * Example Usage:
 * @code
 * StackMemoryTracker stackTracker;
 * // Code execution
 * stackTracker.Add_Track_Point(); // Track current stack pointer
 * // More code execution
 * stackTracker.Print_Memory_From_Last_Point(); // Print memory used since the last track point
 * @endcode
 */

class StackMemoryTracker
{
public:
    /**
     * @brief Constructor that initializes the stack memory tracker.
     *
     * In `DEBUG_MODE`, this constructor captures the current stack pointer and records it
     * as the initial tracking point. The initial point serves as the reference for
     * calculating subsequent stack memory usage.
     */
    StackMemoryTracker();

    /**
     * @brief Destructor that clears all tracked memory points.
     *
     * In `DEBUG_MODE`, the destructor clears the stack of tracked memory points.
     */
    ~StackMemoryTracker();

    /**
     * @brief Prints the current stack size relative to the initial track point.
     *
     * In `DEBUG_MODE`, this function prints the current size of the stack by calculating
     * the difference between the current stack pointer and the initial tracked pointer.
     */
    void Print_Current_Stack_Size();

    /**
     * @brief Gets the current stack size relative to the initial track point.
     *
     * In `DEBUG_MODE`, this function calculates and returns the size of the stack by
     * subtracting the current stack pointer from the initial tracked stack pointer.
     *
     * @return The current stack size in bytes. Returns 0 if `DEBUG_MODE` is not defined.
     */
    int Get_Current_Stack_Size();

    /**
     * @brief Adds a new track point for stack memory tracking.
     *
     * In `DEBUG_MODE`, this function pushes the current stack pointer onto the internal
     * stack of tracked points. The added point can later be used to measure the stack memory
     * used since this point.
     */
    void Add_Track_Point();

    /**
     * @brief Prints the memory used from the last tracked point.
     *
     * In `DEBUG_MODE`, this function calculates and prints the amount of memory used on the
     * stack since the last tracked point (pushed via `Add_Track_Point()`).
     */
    void Print_Memory_From_Last_Point();

    /**
     * @brief Pops the last tracked point from the stack and prints the memory used.
     *
     * In `DEBUG_MODE`, this function removes the most recent track point from the internal
     * stack and prints the memory used on the stack since that point.
     */
    void Pop_Last_Point();

private:
#ifdef DEBUG_MODE
    /**
     * @brief Stores stack pointers at different track points.
     *
     * This stack holds pointers to the memory locations on the stack where tracking
     * began. The top of the stack represents the most recent track point.
     */
    std::stack<void*> m_memory_points;

    /**
     * @brief The stack pointer at the time of construction (initial tracking point).
     */
    void* m_memory_begin;
#endif /* DEBUG_MODE */
};

/**
 * @brief Destructor that clears all tracked memory points.
 *
 * This destructor pops all tracked memory points from the internal stack.
 * It ensures no memory points remain in the `m_memory_points` stack.
 */
inline StackMemoryTracker::~StackMemoryTracker()
{
#ifdef DEBUG_MODE
    while(!m_memory_points.empty())
    {
        m_memory_points.pop();
    }
#endif /* DEBUG_MODE */
}

/**
 * @brief Constructor that initializes the stack memory tracker.
 *
 * Captures the current stack pointer using inline assembly and stores it as the initial
 * tracking point in `m_memory_begin`. The same pointer is also pushed to the internal
 * `m_memory_points` stack.
 */
inline StackMemoryTracker::StackMemoryTracker()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr)); // Capture current stack pointer
    m_memory_begin = stack_ptr;
    m_memory_points.push(stack_ptr);
#endif /* DEBUG_MODE */
}

/**
 * @brief Gets the current stack size relative to the initial track point.
 *
 * Captures the current stack pointer and calculates the difference between it and
 * `m_memory_begin`. Returns the stack size in bytes.
 *
 * @return The current stack size in bytes, or 0 if `DEBUG_MODE` is not defined.
 */
inline int StackMemoryTracker::Get_Current_Stack_Size()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr)); // Capture current stack pointer
    return static_cast<char*>(stack_ptr) - static_cast<char*>(m_memory_begin);
#endif /* DEBUG_MODE */
    return 0;
}

/**
 * @brief Prints the current stack size relative to the initial track point.
 *
 * Captures the current stack pointer, calculates the stack size used since
 * the initial track point, and prints the result to the debug log.
 */
inline void StackMemoryTracker::Print_Current_Stack_Size()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr)); // Capture current stack pointer
    Debug_Log("Stack pointer: ", static_cast<char*>(m_memory_begin) - static_cast<char*>(stack_ptr), "bytes");
#endif /* DEBUG_MODE */
}

/**
 * @brief Adds a new track point for stack memory tracking.
 *
 * Captures the current stack pointer and pushes it onto the internal `m_memory_points` stack.
 */
inline void StackMemoryTracker::Add_Track_Point()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr)); // Capture current stack pointer
    m_memory_points.push(stack_ptr);
#endif /* DEBUG_MODE */
}

/**
 * @brief Prints the memory used from the last tracked point.
 *
 * Captures the current stack pointer and calculates the memory usage since
 * the most recent track point, which is stored at the top of the `m_memory_points` stack.
 * Prints the result to the debug log.
 */
inline void StackMemoryTracker::Print_Memory_From_Last_Point()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr)); // Capture current stack pointer
    Debug_Log("Stack pointer: ", static_cast<char*>(stack_ptr) - static_cast<char*>(m_memory_points.top()), "bytes");
#endif /* DEBUG_MODE */
}

/**
 * @brief Pops the last tracked point and prints the memory used since that point.
 *
 * Removes the most recent track point from the `m_memory_points` stack and prints
 * the memory used since that point. After popping, the top of the stack now holds
 * the next most recent track point.
 */
inline void StackMemoryTracker::Pop_Last_Point()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr)); // Capture current stack pointer
    Debug_Log("Stack pointer(popped): ", static_cast<char*>(stack_ptr) - static_cast<char*>(m_memory_points.top()), "bytes");
    m_memory_points.pop();
#endif /* DEBUG_MODE */
}

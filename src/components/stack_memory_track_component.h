#pragma once

/*
 * Tracks the memory on the stack in bytes relativly acurate. It does so by storing the stack pointer
 * at different points and Printting the difference by subtracting the 2 points. The stack grows
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

class StackMemoryTracker
{
public:
    StackMemoryTracker();
    ~StackMemoryTracker();
    void Print_Current_Stack_Size();
    int Get_Current_Stack_Size();
    void Add_Track_Point();
    void Print_Memory_From_Last_Point();
    void Pop_Last_Point();
private:
#ifdef DEBUG_MODE
    /* stores the stack pointer at creation time(construction) */
    std::stack<void*> m_memory_points;
    void* m_memory_begin;
#endif /* DEBUG_MODE */
};

inline StackMemoryTracker::~StackMemoryTracker()
{
    while(!m_memory_points.empty())
    {
        m_memory_points.pop();
    }
}

inline StackMemoryTracker::StackMemoryTracker()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    m_memory_begin = stack_ptr;
    m_memory_points.push(stack_ptr);
#endif /* DEBUG_MODE */
}

inline int StackMemoryTracker::Get_Current_Stack_Size()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    return static_cast<char*>(stack_ptr) - static_cast<char*>(m_memory_begin);
#endif /* DEBUG_MODE */
    return 0;
}

inline void StackMemoryTracker::Print_Current_Stack_Size()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    Debug_Log("Stack pointer: ", static_cast<char*>(m_memory_begin) - static_cast<char*>(stack_ptr), "bytes");
#endif /* DEBUG_MODE */
}

inline void StackMemoryTracker::Add_Track_Point()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    m_memory_points.push(stack_ptr);
#endif /* DEBUG_MODE */
}

inline void StackMemoryTracker::Print_Memory_From_Last_Point()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    Debug_Log("Stack pointer: ", static_cast<char*>(stack_ptr) - static_cast<char*>(m_memory_points.top()), "bytes");
#endif /* DEBUG_MODE */
}

inline void StackMemoryTracker::Pop_Last_Point()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    Debug_Log("Stack pointer(poped): ", static_cast<char*>(stack_ptr) - static_cast<char*>(m_memory_points.top()), "bytes");
    m_memory_points.pop();
#endif /* DEBUG_MODE */
}


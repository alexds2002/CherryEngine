#pragma once

#include <project_definitions.h>
#include <debug_logger_component.h>
#include <stack>

class StackMemoryTracker
{
public:
    StackMemoryTracker();
    void Print_Current_Stack_Size() const;
    void Add_Track_Point();
    void Print_Memory_From_Last_Point() const;
    void Pop_Last_Point();
private:
    /* stores the stack pointer at creation time(construction) */
#ifdef DEBUG_MODE
    std::stack<void*> m_memory_points;
    void* m_memory_begin;
#endif /* DEBUG_MODE */
};

inline StackMemoryTracker::StackMemoryTracker()
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    m_memory_begin = stack_ptr;
#endif /* DEBUG_MODE */
}

inline void StackMemoryTracker::Print_Current_Stack_Size() const
{
#ifdef DEBUG_MODE
    void* stack_ptr;
    asm ("mov %%rsp, %0" : "=r"(stack_ptr));
    Debug_Log("Stack pointer: ", static_cast<char*>(stack_ptr) - static_cast<char*>(m_memory_begin), "bytes");
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

inline void StackMemoryTracker::Print_Memory_From_Last_Point() const
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

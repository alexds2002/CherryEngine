#pragma once

/*
 * The Heap memory tracker is a macro that overloads the new and delete operators,
 * and tracks everything allocated on the heap. Every new call, STL container or smart ptr.
 * This macro is only compiled in DEBUG_MODE to avoid overloading it in RELEASE_MODE.
 * Example Usage:
 * Above the main function:
 * TRACK_HEAP_ONLY()
 * Every time you want to check the heap size:
 * PRINT_HEAP_MEMORY()
 * !!! WARNING !!!
 * The macro defines variables so calliing it multiple times in the same scope will crash the program.
 */

#ifdef DEBUG_MODE
#include <iostream>
#include <cstdlib>
#include <new>
#include <mutex>
#include <atomic>
#include <cstdlib>
#endif

#ifdef DEBUG_MODE
#define TRACK_HEAP_ONLY() \
 \
std::atomic<size_t> total_allocated_memory(0); \
 \
void* operator new(size_t size) { \
    size_t total_size = size + sizeof(size_t); \
    void* ptr = std::malloc(total_size); \
    if (!ptr) { \
        throw std::bad_alloc(); \
    } \
    *static_cast<size_t*>(ptr) = size; \
    total_allocated_memory += size; \
    return static_cast<char*>(ptr) + sizeof(size_t); \
} \
 \
void* operator new[](size_t size) { \
    size_t total_size = size + sizeof(size_t); \
    void* ptr = std::malloc(total_size); \
    if (!ptr) { \
        throw std::bad_alloc(); \
    } \
    *static_cast<size_t*>(ptr) = size; \
    total_allocated_memory += size; \
    return static_cast<char*>(ptr) + sizeof(size_t); \
} \
void operator delete(void* ptr) noexcept { \
    if (ptr) { \
        void* original_ptr = static_cast<char*>(ptr) - sizeof(size_t); \
        size_t size = *static_cast<size_t*>(original_ptr); \
        total_allocated_memory -= size; \
        std::free(original_ptr); \
    } \
} \
void operator delete[](void* ptr) noexcept { \
    if (ptr) { \
        void* original_ptr = static_cast<char*>(ptr) - sizeof(size_t); \
        size_t size = *static_cast<size_t*>(original_ptr); \
        total_allocated_memory -= size; \
        std::free(original_ptr); \
    } \
} \
void operator delete(void* ptr, size_t size) noexcept { \
    if (ptr) { \
        total_allocated_memory -= size; \
        std::free(ptr); \
    } \
} \
 \
void operator delete[](void* ptr, size_t size) noexcept { \
    if (ptr) { \
        total_allocated_memory -= size; \
        std::free(ptr); \
    } \
} \
 \
size_t Get_Total_Allocated_Memory() { \
    return total_allocated_memory.load(); \
} \
 \
void Report_Total_Allocated_Memory() { \
    std::cout << "Total allocated memory: " << Get_Total_Allocated_Memory() << " bytes" << std::endl; \
} \
 \
struct MemoryReporter { \
    ~MemoryReporter() { \
        Report_Total_Allocated_Memory(); \
    } \
}; \
 \
static MemoryReporter memoryReporter;
// TRACK_HEAP_ONLY() END
#else
#define TRACK_HEAP_ONLY() (void*)(0);
#endif /* DEBUG_MODE */

#ifdef DEBUG_MODE
#define TRACK_HEAP_AND_LEAKS()\
 \
constexpr size_t MAX_TRACKED_ALLOCATIONS = 107374182; \
 \
struct AllocationRecord { \
    void* ptr; \
    size_t size; \
}; \
 \
std::mutex heap_tracker_mutex; \
AllocationRecord allocation_records[MAX_TRACKED_ALLOCATIONS]; \
size_t allocation_count = 0; \
size_t total_allocated_memory = 0; \
 \
void Add_Allocation(void* ptr, size_t size) { \
    std::lock_guard<std::mutex> guard(heap_tracker_mutex); \
    if (allocation_count < MAX_TRACKED_ALLOCATIONS) { \
        allocation_records[allocation_count++] = { ptr, size }; \
        total_allocated_memory += size; \
    } else { \
        std::cerr << "Warning: Maximum tracked allocations reached." << std::endl; \
    } \
} \
 \
void Remove_Allocation(void* ptr) { \
    std::lock_guard<std::mutex> guard(heap_tracker_mutex); \
    for (size_t i = 0; i < allocation_count; ++i) { \
        if (allocation_records[i].ptr == ptr) { \
            total_allocated_memory -= allocation_records[i].size; \
            allocation_records[i] = allocation_records[--allocation_count]; \
            return; \
        } \
    } \
} \
 \
void* operator new(size_t size) { \
    void* ptr = std::malloc(size); \
    if (!ptr) { \
        throw std::bad_alloc(); \
    } \
    Add_Allocation(ptr, size); \
    return ptr; \
} \
 \
void* operator new[](size_t size) { \
    void* ptr = std::malloc(size); \
    if (!ptr) { \
        throw std::bad_alloc(); \
    } \
    Add_Allocation(ptr, size); \
    return ptr; \
} \
 \
void operator delete(void* ptr) noexcept { \
    if (ptr) { \
        Remove_Allocation(ptr); \
        std::free(ptr); \
    } \
} \
 \
void operator delete[](void* ptr) noexcept { \
    if (ptr) { \
        Remove_Allocation(ptr); \
        std::free(ptr); \
    } \
} \
void operator delete(void* ptr, size_t size) noexcept { \
    if (ptr) { \
        Remove_Allocation(ptr); \
        std::free(ptr); \
    } \
} \
 \
void operator delete[](void* ptr, size_t size) noexcept { \
    if (ptr) { \
        Remove_Allocation(ptr); \
        std::free(ptr); \
    } \
} \
 \
void Report_Leaks() { \
    std::lock_guard<std::mutex> guard(heap_tracker_mutex); \
    if (allocation_count == 0) { \
        std::cout << "No memory leaks detected." << std::endl; \
    } else { \
        std::cout << "Memory leaks detected:" << std::endl; \
        for (size_t i = 0; i < allocation_count; ++i) { \
            std::cout << "Leaked " << allocation_records[i].size << " bytes at address " << allocation_records[i].ptr << std::endl; \
        } \
    } \
} \
 \
struct LeakReporter { \
    ~LeakReporter() { \
        Report_Leaks(); \
    } \
}; \
 \
static LeakReporter leakReporter;
// TRACK_HEAP_AND_LEAKS() END
#else
#define TRACK_HEAP_AND_LEAKS() (void*)(0);
#endif /* DEBUG_MODE */

#ifdef DEBUG_MODE
#define PRINT_HEAP_MEMORY() \
    std::cout << "Current Heap size: " << total_allocated_memory << "bytes" << std::endl;
#else
#define PRINT_HEAP_MEMORY() (void*)(0);
#endif /* DEBUG_MODE */

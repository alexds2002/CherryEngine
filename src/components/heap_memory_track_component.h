#pragma once

#include <iostream>
#include <map>
#include <cstdlib>
#include <new>
#include <mutex>
#include <atomic>
#include <cstdlib>

#define TRACK_MEMORY_ONLY() \
 \
std::atomic<size_t> total_allocated_memory(0); \
 \
void* operator new(size_t size) { \
    size_t totalSize = size + sizeof(size_t); \
    void* ptr = std::malloc(totalSize); \
    if (!ptr) { \
        throw std::bad_alloc(); \
    } \
    *static_cast<size_t*>(ptr) = size; \
    total_allocated_memory += size; \
    return static_cast<char*>(ptr) + sizeof(size_t); \
} \
 \
void* operator new[](size_t size) { \
    size_t totalSize = size + sizeof(size_t); \
    void* ptr = std::malloc(totalSize); \
    if (!ptr) { \
        throw std::bad_alloc(); \
    } \
    *static_cast<size_t*>(ptr) = size; \
    total_allocated_memory += size; \
    return static_cast<char*>(ptr) + sizeof(size_t); \
} \
void operator delete(void* ptr) noexcept { \
    if (ptr) { \
        void* originalPtr = static_cast<char*>(ptr) - sizeof(size_t); \
        size_t size = *static_cast<size_t*>(originalPtr); \
        total_allocated_memory -= size; \
        std::free(originalPtr); \
    } \
} \
void operator delete[](void* ptr) noexcept { \
    if (ptr) { \
        void* originalPtr = static_cast<char*>(ptr) - sizeof(size_t); \
        size_t size = *static_cast<size_t*>(originalPtr); \
        total_allocated_memory -= size; \
        std::free(originalPtr); \
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
size_t getTotalAllocatedMemory() { \
    return total_allocated_memory.load(); \
} \
 \
void reportTotalAllocatedMemory() { \
    std::cout << "Total allocated memory: " << getTotalAllocatedMemory() << " bytes" << std::endl; \
} \
 \
struct MemoryReporter { \
    ~MemoryReporter() { \
        reportTotalAllocatedMemory(); \
    } \
}; \
 \
static MemoryReporter memoryReporter;
// TRACK_MEMORY_ONLY() END

#define TRACK_MEMORY_AND_LEAKS()\
 \
constexpr size_t MAX_TRACKED_ALLOCATIONS = 107374182; \
 \
struct AllocationRecord { \
    void* ptr; \
    size_t size; \
}; \
 \
std::mutex heapTrackerMutex; \
AllocationRecord allocationRecords[MAX_TRACKED_ALLOCATIONS]; \
size_t allocationCount = 0; \
size_t totalAllocatedMemory = 0; \
 \
void addAllocation(void* ptr, size_t size) { \
    std::lock_guard<std::mutex> guard(heapTrackerMutex); \
    if (allocationCount < MAX_TRACKED_ALLOCATIONS) { \
        allocationRecords[allocationCount++] = { ptr, size }; \
        totalAllocatedMemory += size; \
    } else { \
        std::cerr << "Warning: Maximum tracked allocations reached." << std::endl; \
    } \
} \
 \
void removeAllocation(void* ptr) { \
    std::lock_guard<std::mutex> guard(heapTrackerMutex); \
    for (size_t i = 0; i < allocationCount; ++i) { \
        if (allocationRecords[i].ptr == ptr) { \
            totalAllocatedMemory -= allocationRecords[i].size; \
            allocationRecords[i] = allocationRecords[--allocationCount]; \
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
    addAllocation(ptr, size); \
    return ptr; \
} \
 \
void operator delete(void* ptr) noexcept { \
    if (ptr) { \
        removeAllocation(ptr); \
        std::free(ptr); \
    } \
} \
 \
void* operator new[](size_t size) { \
    void* ptr = std::malloc(size); \
    if (!ptr) { \
        throw std::bad_alloc(); \
    } \
    addAllocation(ptr, size); \
    return ptr; \
} \
 \
void operator delete[](void* ptr) noexcept { \
    if (ptr) { \
        removeAllocation(ptr); \
        std::free(ptr); \
    } \
} \
 \
void reportLeaks() { \
    std::lock_guard<std::mutex> guard(heapTrackerMutex); \
    if (allocationCount == 0) { \
        std::cout << "No memory leaks detected." << std::endl; \
    } else { \
        std::cout << "Memory leaks detected:" << std::endl; \
        for (size_t i = 0; i < allocationCount; ++i) { \
            std::cout << "Leaked " << allocationRecords[i].size << " bytes at address " << allocationRecords[i].ptr << std::endl; \
        } \
    } \
} \
 \
struct LeakReporter { \
    ~LeakReporter() { \
        reportLeaks(); \
    } \
}; \
 \
static LeakReporter leakReporter;
// TRACK_MEMORY_AND_LEAKS() END

#pragma once

#include "thread_pool.h"

// Assumption: the + - / * operators represent some important algorithm, obviously for
// such simple calculation there is no need for more complex design patterns and code repetition.

// The vectors can be preallocated if we know the size of the data,
// also they can be passed by reference instead of created in the strategy and then returned.
// The vectors can be arrays that live on the stack which would result in even more cache hits!
// note: Using ThreadPool just because i recently developed it, there is no need for it here.

// Interface for the strategies
class OperationStrategy
{
public:
    // Defines a pure virtual function that operates on two rows. We can have multiple types of operations.
    virtual std::vector<int> ExecuteColumnAlgorithm(const std::vector<int>& col1, const std::vector<int>& col2) = 0;
    // Avoid potential leak or improper cleanups
    virtual ~OperationStrategy() = default;
};

class AdditionStrategy : public OperationStrategy
{
public:
    std::vector<int> ExecuteColumnAlgorithm(const std::vector<int>& col1, const std::vector<int>& col2) final override
    {
        std::vector<int> result;
        // assumes that both columns are the same size and are valid
        result.resize(col1.size());
        const uint32_t numberOfThreads = std::thread::hardware_concurrency();
        ThreadPool pool(numberOfThreads);
        std::vector<std::future<bool>> futures;
        for(int threadIdx = 0; threadIdx < numberOfThreads; ++threadIdx)
        {
            // capture threadIdx by copy
            futures.push_back(pool.Add_Task([&, threadIdx]()
            {
                for (size_t i = threadIdx * col1.size() / numberOfThreads; i < (threadIdx + 1) * col1.size() / numberOfThreads; ++i)
                {
                    result[i] = (col1[i] + col2[i]);
                }
                return true; // signal that the job is complete and succesful
            }));
        }
        // wait for all of the threads to finish the work
        for(auto& future : futures)
        {
            bool success = future.get();
            if(!success) std::cerr << "One or more of the threads failed!\n";
        }
        return result;
    }
};

class SubtractionStrategy : public OperationStrategy
{
public:
    std::vector<int> ExecuteColumnAlgorithm(const std::vector<int>& col1, const std::vector<int>& col2) final override
    {
        std::vector<int> result;
        // assumes that both columns are the same size and are valid
        result.resize(col1.size());
        const uint32_t numberOfThreads = std::thread::hardware_concurrency();
        ThreadPool pool(numberOfThreads);
        std::vector<std::future<bool>> futures;
        for(int threadIdx = 0; threadIdx < numberOfThreads; ++threadIdx)
        {
            // capture threadIdx by copy
            futures.push_back(pool.Add_Task([&, threadIdx]()
            {
                for (size_t i = threadIdx * col1.size() / numberOfThreads; i < (threadIdx + 1) * col1.size() / numberOfThreads; ++i)
                {
                    result[i] = (col1[i] - col2[i]);
                }
                return true; // signal that the job is complete and succesful
            }));
        }
        // wait for all of the threads to finish the work
        for(auto& future : futures)
        {
            bool success = future.get();
            if(!success) std::cerr << "One or more of the threads failed!\n";
        }
        return result;
    }
};

class MultiplicationStrategy : public OperationStrategy {
public:
    std::vector<int> ExecuteColumnAlgorithm(const std::vector<int>& col1, const std::vector<int>& col2) final override
    {
        std::vector<int> result;
        // assumes that both columns are the same size and are valid
        result.resize(col1.size());
        const uint32_t numberOfThreads = std::thread::hardware_concurrency();
        ThreadPool pool(numberOfThreads);
        std::vector<std::future<bool>> futures;
        for(int threadIdx = 0; threadIdx < numberOfThreads; ++threadIdx)
        {
            // capture threadIdx by copy
            futures.push_back(pool.Add_Task([&, threadIdx]()
            {
                for (size_t i = threadIdx * col1.size() / numberOfThreads; i < (threadIdx + 1) * col1.size() / numberOfThreads; ++i)
                {
                    result[i] = (col1[i] * col2[i]);
                }
                return true; // signal that the job is complete and succesful
            }));
        }
        // wait for all of the threads to finish the work
        for(auto& future : futures)
        {
            bool success = future.get();
            if(!success) std::cerr << "One or more of the threads failed!\n";
        }
        return result;
    }
};

// Note:
// can also return float, double or long double if we want that behaviour
class DivisionStrategy : public OperationStrategy
{
public:
    std::vector<int> ExecuteColumnAlgorithm(const std::vector<int>& col1, const std::vector<int>& col2) final override
    {
        std::vector<int> result;
        // assumes that both columns are the same size and are valid
        result.resize(col1.size());
        const uint32_t numberOfThreads = std::thread::hardware_concurrency();
        ThreadPool pool(numberOfThreads);
        std::vector<std::future<bool>> futures;
        for(int threadIdx = 0; threadIdx < numberOfThreads; ++threadIdx)
        {
            // capture threadIdx by copy
            futures.push_back(pool.Add_Task([&, threadIdx]()
            {
                for (size_t i = threadIdx * col1.size() / numberOfThreads; i < (threadIdx + 1) * col1.size() / numberOfThreads; ++i)
                {
                    if(col2[i] == 0)
                    {
                        // or terminate the program
                        std::cout << "ERROR: Trying to divide by zero!" << i << ".\n";
                        result[i] = 0;
                    }
                    else
                    {
                        result[i] = (col1[i] / col2[i]);
                    }
                }
                return true; // signal that the job is complete and succesful
            }));
        }
        // wait for all of the threads to finish the work
        for(auto& future : futures)
        {
            bool success = future.get();
            if(!success) std::cerr << "One or more of the threads failed!\n";
        }
        return result;
    }
};


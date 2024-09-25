#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class deque {
private:
    std::vector<T*> chunks;
    int chunk_size;
    int front_index;  // Index in the first chunk
    int back_index;   // Index in the last chunk
    int front_chunk;  // Index of the front chunk
    int back_chunk;   // Index of the back chunk
    int num_chunks;

    void addFrontChunk()
    {
        T* new_chunk = new T[chunk_size];
        chunks.insert(chunks.begin(), new_chunk);
        front_chunk++;
        back_chunk++;
        num_chunks++;
    }

    void addBackChunk()
    {
        T* new_chunk = new T[chunk_size];
        chunks.push_back(new_chunk);
        num_chunks++;
    }

public:
    // a size of each chunk can be provided
    deque(int chunk_size = 10) : chunk_size(chunk_size), front_index(0),
                                 back_index(0), front_chunk(0),
                                 back_chunk(0), num_chunks(1)
    {
        T* initial_chunk = new T[chunk_size];
        chunks.push_back(initial_chunk);
    }

    ~deque()
    {
        for (T* chunk : chunks)
        {
            delete[] chunk;
        }
    }

    inline bool isEmpty() const noexcept
    {
        return front_chunk == back_chunk && front_index == back_index;
    }

    inline int getSize() const noexcept
    {
        return (back_chunk - front_chunk) * chunk_size + (back_index - front_index);
    }

    void pushFront(const T& value)
    {
        if (front_index == 0) {
            addFrontChunk();
            front_index = chunk_size;
        }
        front_index--;
        chunks[front_chunk][front_index] = value;
    }

    void pushBack(const T& value)
    {
        if (back_index == chunk_size) {
            addBackChunk();
            back_index = 0;
            back_chunk++;
        }
        chunks[back_chunk][back_index] = value;
        back_index++;
    }

    void popFront()
    {
        if (isEmpty())
        {
            std::cerr << "deque is empty, cannot pop front!" << std::endl;
            return;
        }
        front_index++;
        if (front_index == chunk_size) {
            front_chunk++;
            front_index = 0;
        }
    }

    void popBack()
    {
        if (isEmpty())
        {
            std::cerr << "deque is empty, cannot pop back!" << std::endl;
            return;
        }
        back_index--;
        if (back_index < 0) {
            back_chunk--;
            back_index = chunk_size - 1;
        }
    }

    T& getFront() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("deque is empty");
        }
        return chunks[front_chunk][front_index];
    }

    T& getBack() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("deque is empty");
        }
        return chunks[back_chunk][back_index - 1];
    }
};


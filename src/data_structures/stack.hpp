#ifndef STACK_HPP
#define STACK_HPP

#define MIN_STACK_SIZE 10

#include <utility>

namespace atl
{
#ifndef size_t
#define size_t unsigned long long
#endif

template <typename T>
class stack
{
public:
    ~stack() { delete[] data_; }
    stack()
    {
        data_ = new T[MIN_STACK_SIZE];
        capacity_ = MIN_STACK_SIZE;
    }
    stack(T val)
    {
        data_ = new T[MIN_STACK_SIZE];
        capacity_ = MIN_STACK_SIZE;
        data_[current_size_++] = val;
    }
    stack(T&& val)
    {
        data_ = new T[MIN_STACK_SIZE];
        capacity_ = MIN_STACK_SIZE;
        data_[current_size_++] = val;
    }
    void push(T& val)
    {
        if(current_size_ < capacity_)
        {
            data_[current_size_++] = val;
        }
        else
        {
            enlarge_();
            data_[current_size_++] = val;
        }
    }
    void push(T&& val)
    {
        if(current_size_ < capacity_)
        {
            data_[current_size_++] = val;
        }
        else
        {
            enlarge_();
            data_[current_size_++] = val;
        }
    }

private:
    void enlarge_()
    {
        T* new_container = new T[capacity_ * 2];
        for(int i = 0; i < capacity_; ++i)
        {
            new_container[i] = data_[i];
        }
        delete[] data_;
        data_ = new_container;
        capacity_ = capacity_ * 2;
    }

    T* data_;
    size_t current_size_{0};
    size_t capacity_{0};

};

}

#endif // !STACK_HPP


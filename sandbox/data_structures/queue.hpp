#include "linkedList.hpp"

template <typename T>
class queue
{
public:
    ~queue() {}
    queue() {}
    void push(T val)
    {
        data_.push_back(val);
    }
    void pop()
    {
        data_.pop_back();
    }
    void print()
    {
        data_.print_list();
    }

private:
    atl::List<T> data_;
};


#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstring>

template<class T>
class vector
{
public:
    using Iterator = T*;
    vector();
    size_t size() const;
    size_t capacity() const;
    void push_back(T value);
    void pop_back();
    T at(size_t index) const;
    void PrintElements() const;
    void erase(size_t index);
    void erase(Iterator begin, Iterator end);
    Iterator begin() const
    {
        return &m_elementsArr[0];
    }
    Iterator end() const
    {
        return &m_elementsArr[m_currentSize]; /* returns addres of one element after the end */
    }
    ~vector();
private:
    T* m_elementsArr;
    size_t m_currentSize;
    size_t m_capacity;

public:
    static constexpr size_t m_maxAllowedSize = __UINT64_MAX__; /* used to make sure the vector doesnt go over surtain size */
};

#include "vector.hpp" /* all the vector implementation has to be in one header since it is a template */

#endif /* VECTOR_H */

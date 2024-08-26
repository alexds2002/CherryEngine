#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include <vector>

template <class T>
class unordered_map
{
public:
    bool IsEmpty() const;
    void InsertItem(const std::string& key, T value);
    void RemoveItem(const std::string& key);
    T operator[](const std::string& key)
    {
        return ValueAtIndex(key);
    }
    
    using Iterator = typename std::vector<std::pair<std::string, T>*>::iterator;

    // TODO: Overload the -> operator to fix the iterators
    // std::pair<std::string, T>* operator->()
    // {
    //     return m_IndexVector[0];
    // }

    Iterator begin()
    {
        return m_IndexVector.begin();
    }
    Iterator end()
    {
        return m_IndexVector.end();
    }
    ~unordered_map() { }
private:
    static constexpr int m_hashGroups = 50000;

    std::list<std::pair<std::string, T>> m_tableGroups[m_hashGroups];

    std::vector<std::pair<std::string, T>*> m_IndexVector;

    T ValueAtIndex(const std::string& key);

    int HashFunction(const std::string& key);

};

#include "unordered_map.hpp"

#endif /* UNORDERED_MAP_H */
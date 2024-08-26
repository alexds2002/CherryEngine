#ifndef UNORDERED_MAP_HPP
#define UNORDERED_MAP_HPP

#include "unordered_map.h"
#include <iostream>
#include <algorithm>

template <class T>
bool unordered_map<T>::IsEmpty() const
{
    for(int i = 0; i < m_hashGroups; ++i)
    {
        if(m_tableGroups[i].size() != 0)
        {
            return false;
        }
    }
    return true;
}

template <class T>
int unordered_map<T>::HashFunction(const std::string& key)
{
    //std::hash(key)
    int i = 0;
    for(int j = 0; j < key.length(); j++)
    {
        i += key[j];
    }
    return i % m_hashGroups;
}

template <class T>
void unordered_map<T>::InsertItem(const std::string& key, T value)
{
    int index = HashFunction(key);
    std::pair<std::string, T> inputPair(key, value);
    bool bKeyExists = false;
    for(auto itrBegin = m_tableGroups[index].begin(); itrBegin != m_tableGroups[index].end(); itrBegin++)
    {
        if(itrBegin->first == key)
        {
            bKeyExists = true;
            itrBegin->second = value;
            break;
        }
    }
    if(!bKeyExists)
    {
        m_tableGroups[index].push_back(inputPair);
        m_IndexVector.push_back(&(m_tableGroups[index].front()));
    }
}

template <class T>
T unordered_map<T>::ValueAtIndex(const std::string& key)
{
    int index = HashFunction(key);
    std::cout << "Here" << std::endl;
    for (auto itr = m_tableGroups[index].begin(); itr != m_tableGroups[index].end(); itr++)
    {
        std::cout << "Here2" << std::endl;
        if(itr->first == key)
        {
            return itr->second;
        }
    }
    std::cout << "Here3" << std::endl;
    // return -1 indicating an error
    return -1;
}

template <class T>
void unordered_map<T>::RemoveItem(const std::string& key)
{
    int index = HashFunction(key);
    for(auto itr = m_IndexVector.begin(); itr != m_IndexVector.end(); itr++)
    {
        if (*itr == &(m_tableGroups[index].front()))
        {
            m_IndexVector.erase(itr);
            m_tableGroups[index].clear();
        }
    }
}


#endif /* UNORDERED_MAP_HPP  */

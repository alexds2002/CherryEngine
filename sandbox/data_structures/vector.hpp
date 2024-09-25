#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector.h"

template<class T>
vector<T>::vector()
{
    m_elementsArr = new T[1];
    m_capacity = 1;
    m_currentSize = 0;
}

template<class T>
size_t vector<T>::size() const
{
    return m_currentSize;
}

template<class T>
void vector<T>::push_back(T value)
{
    if(m_currentSize >= m_capacity)
    {
        m_capacity *= 2;
        T* temp = new T[2 * m_capacity];

        std::memcpy(temp, m_elementsArr, sizeof(T) * m_currentSize); // ! previously has bug with sizeof(m_elementsArr)

        delete [] m_elementsArr;
        m_elementsArr = temp;

        m_elementsArr[m_currentSize++] = value;
    }
    else
    {
        m_elementsArr[m_currentSize++] = value;
    }
}

template<class T>
size_t vector<T>::capacity() const
{
    return m_capacity;
}

template<class T>
T vector<T>::at(size_t index) const
{
    if(index >= m_currentSize - 1)
    {
        std::wcerr << "Index out of range error\n ";
        std::wcerr.flush();
        exit(EXIT_FAILURE);
    }
    return m_elementsArr[index];
}

template<class T>
void vector<T>::PrintElements() const
{
    for(int i = 0; i < m_currentSize; ++i)
    {
        std::cout << m_elementsArr[i] << std::endl;
    }
}

template<class T>
void vector<T>::pop_back()
{
    m_currentSize--;
}

template<class T>
vector<T>::~vector()
{
    delete [] m_elementsArr;
}

template<class T>
void vector<T>::erase(size_t index)
{
    for(int i = index; i < m_currentSize; i++)
    {
        std::memcpy(&m_elementsArr[index], &m_elementsArr[index + 1], sizeof(T) * (m_currentSize - index));
    }
    m_currentSize--;
}

template<class T>
void vector<T>::erase(Iterator begin, Iterator End)
{
    size_t elementsToErase = End - begin;
    size_t elementsToTheEnd = end() - End; /* the end of the array - the last element that we want deleted */

    std::memcpy(begin, End, sizeof(T) * elementsToTheEnd); /*  */
    m_currentSize -= elementsToErase;
}

#endif /* VECTOR_HPP */

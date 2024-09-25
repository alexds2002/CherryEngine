#pragma once

#include <vector>

namespace CherryMath
{

inline void bubble_sort(std::vector<int>& _nums)
{
    bool swapped = false;
    for(int i = 0; i < _nums.size(); ++i)
    {
        for(int j = 0; j < _nums.size() - 1 - i; ++j)
        {
            if(_nums[j] < _nums[j + 1])
            {
                // swap
                _nums[j]     = _nums[j] ^ _nums[j + 1];
                _nums[j + 1] = _nums[j] ^ _nums[j + 1];
                _nums[j]     = _nums[j] ^ _nums[j + 1];
                swapped = true;
            }
        }
        if(!swapped)
        {
            break;
        }
    }
}

inline void insertion_sort(std::vector<int>& _nums)
{
    for(int i = 1; i < _nums.size(); ++i)
    {
        int j = i + 1;
        int key = _nums[i];
        while(j >= 0 && _nums[j] > key)
        {
            _nums[j + 1] = _nums[j];
            --j;
        }
        _nums[j + 1] = key;
    }
}

inline void merge_elements(std::vector<int>& _nums, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> L(n1), R(n2);
    for(int i = 0; i < n1; ++i) { L[i] = _nums[left + i]; }
    for(int i = 0; i < n1; ++i) { R[i] = _nums[middle + 1 + i]; }

    int i = 0, j = 0;
    int k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            _nums[k] = L[i];
            i++;
        }
        else
        {
            _nums[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        _nums[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        _nums[k] = R[j];
        j++;
        k++;
    }
}
inline void merge_sort(std::vector<int>& _nums, int left, int right)
{
    if(_nums.size() <= 1 || left >= right) { return; }

    int middle = (left + right) / 2;
    merge_sort(_nums, left, middle);
    merge_sort(_nums, middle, right);
    merge_elements(_nums, left, middle, right);
}

}


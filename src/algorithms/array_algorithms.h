#pragma once

#include <vector>
#include <utility>
#include <stdint.h>
#include <algorithm>
#include <unordered_map>

namespace CherryMath
{

// needs to be a square
// O(n2)
inline std::vector<std::vector<int>> rotate_image_ninety_degrees(std::vector<std::vector<int>> _image)
{
    if(_image.size() == 0) return{};
    std::vector<std::vector<int>> result_vector(_image.size(), std::vector<int>(_image.size(), 0));
    for(int i = 0; i < _image.size(); ++i)
    {
        for(int j = 0; j < _image.at(i).size(); ++j)
        {
            result_vector[j][_image.size() - i - 1] = _image[i][j];
        }
    }
    return result_vector;
}

inline std::pair<int, int> two_sum(std::vector<int> _input, int sum)
{
    std::unordered_map<int, int> seek_map;
    for(int i = 0; i < _input.size(); ++i)
    {
        if(seek_map.count(sum - _input[i]))
        {
            return std::make_pair(i, seek_map[sum - _input[i]]);
        }
        else
        {
            seek_map[_input[i]] = i;
        }
    }
    return {};
}

inline std::vector<int> three_some(std::vector<int> _input, int sum)
{
    std::unordered_map<int, int> seek_map;

    for (int i = 0; i < _input.size(); ++i)
    {
        for (int j = i + 1; j < _input.size(); ++j)
        {
            int seek_number = sum - _input[i] - _input[j];
            if(seek_map.count(seek_number))
            {
                return { seek_map[seek_number], i, j };
            }
            else
            {
                seek_map[_input[j]] = j;
            }
        }
    }
    return {};
}

/* _input array must be sorted */
inline int binary_search(std::vector<int> _input, int search)
{
    int start = 0;
    int end = _input.size() - 1;
    int middle = 0;
    while(start <= end)
    {
        middle = (end + start) / 2;
        if(_input[middle] > search)
        {
            end = middle - 1;
        }
        else if(_input[middle] < search)
        {
            start = middle + 1;
        }
        else return middle;
    }
    return -1;
}

// 5 3 1 4 9 6 9
inline size_t longest_increasing_sequence(const std::vector<int>& _input)
{
    std::vector<size_t> lengts(_input.size(), 1);

    // O(n2)
    for(int i = _input.size() - 1; i > 0; --i)
    {
        for(int j = i + 1; j < _input.size(); ++j)
        {
            if(_input[i] < _input[j])
            {
                lengts[i] = std::max(lengts[i], lengts[j] + 1);
            }
        }
    }
    // O(n)
    size_t result = *std::max_element(lengts.begin(), lengts.end());
    return result;
}

// 1 2 -5   5 -3 2 3
inline int64_t max_subarray(const std::vector<int>& _input)
{
    if(_input.size() == 0) return 0;
    int64_t result = INT64_MIN;
    int64_t curr_sum = 0;

    for(int i = 0; i < _input.size(); ++i)
    {
        curr_sum += _input[i];

        result = std::max(result, curr_sum);

        curr_sum = std::max(curr_sum, 0l);
    }

    return result;
}

inline std::vector<int> k_most_frequent_nums(const std::vector<int>& _input, int k)
{
    std::vector<int> result{};
    std::vector<std::vector<int>> histogram(_input.size(), std::vector<int>());
    std::unordered_map<int, int> umap;
    int counter{0};

    for(int i = 0; i < _input.size(); ++i)
    {
        umap[_input[i]]++;
    }
    for(auto pr : umap)
    {
        histogram[pr.second].push_back(pr.first);
    }
    for(int i = histogram.size() - 1; i >= 0; --i)
    {
        if(histogram[i].size() != 0)
        {
            for(int j = 0; j < histogram[i].size(); ++j)
            {
                result.push_back(histogram[i][j]);
                --k;
                if(k == 0) return result;
            }
        }
    }
    return result;
}

} /* namespace CherryMath */

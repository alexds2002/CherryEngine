#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <unordered_map>

namespace CherryMath
{

/* must be null terminated '\0' */
inline size_t size_of_c_styled_string(char* _input)
{
    size_t size = 0;
    while(_input[size] != '\0') { size++; }
    return size;
}

inline void print_c_styled_string(char* _input)
{
    int i = 0;
    while(_input[i] != '\0')
    {
        std::cout << _input[i];
    }
}

inline bool all_unique_chars(const std::string& _input)
{
    /*** histogram solution ***/
    bool histogram[256] = { false };
    for(int i = 0; i < _input.size(); ++i)
    {
        if(histogram[_input[i]] == true) return false;
        histogram[_input[i]] = true;
    }
    return true;
    /*** histogram solution end ***/

    /*** bit manipulation solution ***/
    // only lower case a - z works as it is stored in 32 bit mask
    // 64bit would work for upper case as well, again asuming no extra characters
    /*int checker = 0;
    for (int i = 0; i < _input.size(); ++i) {
        int val = _input[i] - 'a';
        if ((checker & (1 << val)) > 0) return false;
        checker |= (1 << val);
    }
    return true;*/
    /*** bit manipulation solution end ***/

    /*** no extra memory solution ***/
    /*for(int i = 0; i < _input.size(); ++i)
    {
        for(int j = i + 1; j < _input.size(); ++j)
        {
            if(_input[i] == _input[j]) return false;
        }
    }
    return true;*/
    /*** no extra memory solution end ***/

    /*** hash_set solution ***/
    /*std::unordered_map<int, int> umap;
    for(int i = 0; i < _input.size(); ++i)
    {
        if(umap.count(_input[i]) > 0)
        {
            return false;
        }
        umap[_input[i]]++;
    }
    return true;*/
    /*** hash_set solution end ***/
}

inline void reverse_c_styled_string(char* _input)
{
    if(!_input) return;

    int i = 0;
    int j = size_of_c_styled_string(_input) - 1;
    while( i <= j )
    {
        // swap values
        _input[i] = _input[i] ^ _input[j];
        _input[j] = _input[i] ^ _input[j];
        _input[i] = _input[i] ^ _input[j];
        ++i; --j;
    }
}

inline bool is_anagram_c_styled_string(char* _input_a, char* _input_b)
{
    // unordered map initilizes int with value of 0 by default
    std::unordered_map<char, int> ch_map;
    for(int i = 0; i < size_of_c_styled_string(_input_a); ++i)
    {
        ch_map[_input_a[i]]++;
    }
    for(int i = 0; i < size_of_c_styled_string(_input_b); ++i)
    {
        ch_map[_input_b[i]]--;
    }
    for(const auto& elem : ch_map)
    {
        if(elem.second != 0) return false;
    }
    return true;
}

inline bool is_palindrome_c_styled_string(char* _input)
{
    size_t end = size_of_c_styled_string(_input) - 1;
    size_t begin = 0;
    while(begin <= end) { if(_input[end--] != _input[begin++]) return false; }
    return true;
}

inline std::string compress_string(const std::string& _input)
{
    std::string result{};
    for(int i = 0; i < _input.size(); ++i)
    {
        int j = i;
        while(j < _input.size() && (_input[j] == _input[i]))
        {
            ++j;
        }
        result.append(_input[i] + std::to_string(j - i));
        i = j - 1;
    }
    return result;
}

/* must follow letter/number standard: A6l1e1x1 */
inline std::string uncompress_string(const std::string& _input)
{
    std::string result{};

    for(int i = 0; i < _input.size(); ++i)
    {
        result.append(std::string(_input[i + 1] - 48, _input[i]));
        ++i;
    }
    return result;
}

} /* namespace CherryMath */

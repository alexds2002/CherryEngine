#pragma once

#include <utility>

template <typename T>
struct heap
{
    explicit heap() : left{nullptr}, right{nullptr}, data{} {}
    explicit heap(T data_) : left{nullptr}, right{nullptr}, data{data_} {}
    explicit heap(const T& data_) : left{nullptr}, right{nullptr}, data{data_} {}
    explicit heap(T&& data_) : left{nullptr}, right{nullptr}, data{std::move(data_)} {}

    void insert(T val)
    {
    }

private:
    heap<T>* left;
    heap<T>* right;
    T data;
};

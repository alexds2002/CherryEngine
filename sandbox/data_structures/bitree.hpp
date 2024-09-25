#pragma once

namespace atl
{
template <typename T>
struct BynaryTree
{
    BynaryTree() = default;
    BynaryTree(T data) : data_{data}, left{nullptr}, right{nullptr} {}
    T data_{};
    BynaryTree<T>* left{nullptr};
    BynaryTree<T>* right{nullptr};
};
}

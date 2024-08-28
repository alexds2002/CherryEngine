#pragma once
#include "../data_structures/bitree.hpp"

namespace CherryMath
{
inline void work_node()
{
}

inline void in_order_traversel(atl::BynaryTree<int>* bi_tree)
{
    // In order
    in_order_traversel(bi_tree->left);
    work_node();
    in_order_traversel(bi_tree->right);

    // Pre order
    work_node();
    in_order_traversel(bi_tree->left);
    in_order_traversel(bi_tree->right);

    // Post order
    in_order_traversel(bi_tree->left);
    in_order_traversel(bi_tree->right);
    work_node();
}

}


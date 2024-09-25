#pragma once
#include "../data_structures/bitree.hpp"
#include <algorithm>

namespace CherryMath
{

inline void work_node()
{
}

template <typename T>
inline void order_traversel(atl::BynaryTree<T>* bi_tree)
{
    // In order
    order_traversel(bi_tree->left);
    work_node();
    order_traversel(bi_tree->right);

    // Pre order
    work_node();
    order_traversel(bi_tree->left);
    order_traversel(bi_tree->right);

    // Post order
    order_traversel(bi_tree->left);
    order_traversel(bi_tree->right);
    work_node();
}

template <typename T>
inline atl::BynaryTree<T>* invert_tree(atl::BynaryTree<T>* root)
{
    if(!root) return nullptr;
    invertTree(root->left);
    invertTree(root->right);

    atl::BynaryTree<T>* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    ///* interesting solution *///
    /*TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;

        TreeNode* node = new TreeNode(root->val);
        node->right = invertTree(root->left);
        node->left = invertTree(root->right);

        return node;
    }*/
}

template <typename T>
inline int traverseMaxDepth(atl::BynaryTree<T>* cur, int depth = 0)
{
    if(!cur) return depth;
    return std::max(traverse(cur->left, depth + 1), traverse(cur->right, depth + 1));
}

template <typename T>
inline bool validate_bst(atl::BynaryTree<T>* cur, int upperLimit, int lowerLimit)
{
    if(!cur) return true;
    if(cur->left && cur->val > cur->left->val) return false;
    else if(cur->right && cur->val < cur->right->val) return false;
    return validate_bst(cur->left, max(upperLimit, cur->val), INT32_MIN) && validate_bst(cur->right, INT32_MAX, std::min(lowerLimit, cur->val));
}

template <typename T>
inline bool traverse_validate_bst(atl::BynaryTree<T>* left, atl::BynaryTree<T>* right)
{
}

}


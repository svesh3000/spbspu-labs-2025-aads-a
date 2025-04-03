#ifndef TREE_HPP
#define TREE_HPP
#include <functional>
#include "treeNode.hpp"

namespace kiselev
{
  template< typename Key, typename Value, typename Cmp = std::less< Key > >
  class BinarySearchTree
  {
  public:
    using value = std::pair< Key, Value >;

    BinarySearchTree();
    void push(Key k, Value v);
    Value get(Key k);
    void pop(Key k);
  private:
    using Node = TreeNode< Key, Value>;

    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    Node* root;
    Cmp cmp;
  };

  template< typename Key, typename Value, typename Cmp >
  BinarySearchTree< Key, Value, Cmp >::BinarySearchTree():
    root(nullptr)
  {}

  template< typename Key, typename Value, typename Cmp >
  void BinarySearchTree< Key, Value, Cmp >::rotateLeft(Node* node)
  {
    Node* child = node->right;
    node->right = child->left;
    if (child->left)
    {
      child->left->parent = node;
    }
    child->parent = node->parent;
    if (!node->parent)
    {
      root = child;
    }
    else if (node == node->parent->left)
    {
      node->parent->left = child;
    }
    else
    {
      node->parent->right = child;
    }
    child->left = node;
    node->parent = child;
  }

  template< typename Key, typename Value, typename Cmp >
  void BinarySearchTree< Key, Value, Cmp >::rotateRight(Node* node)
  {
    Node* child = node->left;
    node->left = child->right;
    if (child->right)
    {
      child->right->parent = node;
    }
    child->parent = node->parent;
    if (!node->parent)
    {
      root = child;
    }
    else if (node == node->parent->right)
    {
      node->parent->right = child;
    }
    else
    {
      node->parent->left = child;
    }
    child->right = node;
    node->parent = child;
  }
}
#endif

#ifndef TREE_HPP
#define TREE_HPP
#include <functional>
#include <cstddef>
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
    void fixInsert(Node* node);
    void fixDelete(Node* node);
    Node* root_;
    Cmp cmp_;
    size_t size_;
  };

  template< typename Key, typename Value, typename Cmp >
  BinarySearchTree< Key, Value, Cmp >::BinarySearchTree():
    root_(nullptr),
    size_(0)
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
      root_ = child;
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
      root_ = child;
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

  template< typename Key, typename Value, typename Cmp >
  void BinarySearchTree< Key, Value, Cmp >::fixInsert(Node* node)
  {
    Node* parent = nullptr;
    Node* grandParent = nullptr;
    while (node != root_ && node->color == Color::RED && node->parent->color == Color::RED)
    {
      parent = node->parent;
      grandParent = parent->parent;
      if (parent == grandParent->left)
      {
        Node* uncle = grandParent->right;
        if (uncle && uncle->color == Color::RED)
        {
          grandParent->color = Color::RED;
          parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          node = grandParent;
        }
        else
        {
          if (node == parent->right)
          {
            rotateLeft(parent);
            node = parent;
            parent = node->parent;
          }
          rotateRight(grandParent);
          std::swap(parent->color, grandParent->color);
          node = parent;
        }
      }
      else
      {
        Node* uncle = grandParent->left;
        if (uncle && uncle->color == Color::RED)
        {
          grandParent->color = Color::RED;
          parent->color = Color::BLACK;
          uncle->color = Color::BLACK;
          node = grandParent;
        }
        else
        {
          if (node == parent->left)
          {
            rotateRight(parent);
            node = parent;
            parent = node->parent;
          }
          rotateLeft(grandParent);
          std::swap(parent->color, grandParent->color);
          node = parent;
        }
      }
    }
    root_->color = Color::BLACK;
  }

  template< typename Key, typename Value, typename Cmp >
  void BinarySearchTree< Key, Value, Cmp >::fixDelete(Node* node)
  {
    while (node && node->color == Color::BLACK)
    {
      if (node == node->parent->left)
      {
        Node* brother = node->parent->right;
        if (brother->color == Color::RED)
        {
          brother->color = Color::BLACK;
          node->parent->color = Color::RED;
          rotateLeft(node->parent);
          brother = node->parent->right;
        }
        if ((!brother->left || brother->left->color == Color::BLACK) && (!brother->right || brother->right == Color::BLACK))
        {
          brother->color = Color::RED;
          node = node->parent;
        }
        else
        {
          if (!brother->right || brother->right->color == Color::BLACK)
          {
            if (brother->left)
            {
              brother->left->color = Color::BLACK;
            }
            brother->color = Color::RED;
            rotateRight(brother);
            brother = node->parent->right;
          }
          brother->color = node->parent->color;
          node->parent->color = Color::BLACK;
          if (brother->right)
          {
            brother->right->color = Color::BLACK;
          }
          rotateLeft(node->parent);
          node = root_;
        }
      }
      else
      {
        Node* brother = node->parent->left;
        if (brother->color == Color::RED)
        {
          brother->color = Color::BLACK;
          node->parent->color = Color::RED;
          rotateRight(node->parent);
          brother = node->parent->left;
        }
        if ((!brother->left || brother->left->color == Color::BLACK) && (!brother->right || brother->right->color == Color::BLACK))
        {
          brother->color = Color::RED;
          node = node->parent;
        }
        else
        {
          if (!brother->left || brother->left->color == Color::BLACK)
          {
            if (brother->right)
            {
              brother->right->color = Color::BLACK;
            }
            brother->color = Color::RED;
            rotateLeft(brother);
            brother = node->parent->left;
          }
          brother->color = node->parent->color;
          node->parent->color = Color::BLACK;
          if (brother->left)
          {
            brother->left->color = Color::BLACK;
          }
          rotateRight(node->parent);
          node = root_;
        }
      }
    }
    node->color = Color::BLACK;
  }
}
#endif

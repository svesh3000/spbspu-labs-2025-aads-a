#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#include <cstddef>
#include <algorithm>
#include <functional>
#include "node.hpp"

namespace abramov
{
  template< class Key, class Value, class Cmp = std::less< Key > >
  struct BinarySearchTree
  {
    BinarySearchTree();
    void insert(const Key &key, const Value &value);
    size_t size() const noexcept;
    bool empty() const noexcept;
    void swap(BinarySearchTree &rhs) noexcept;
    void clear() noexcept;
  private:
    Node< Key, Value > *root_;
    Node< Key, Value > *fake_;
    Cmp cmp_;
    size_t size_;

    void clearNodes(Node< Key, Value > *root) noexcept;
  };

  template< class Key, class Value, class Cmp >
  BinarySearchTree< Key, Value, Cmp >::BinarySearchTree():
    root_(nullptr),
    fake_(new Node< Key, Value >),
    cmp_(Cmp()),
    size_(0)
  {}

  template< class Key, class Value, class Cmp >
  void BinarySearchTree< Key, Value, Cmp >::insert(const Key &key, const  Value &value)
  {
    if (empty())
    {
      root_ = new Node< Key, Value >(std::make_pair(key, value), nullptr, fake_, fake_, 1);
      ++size_;
      return;
    }
    Node< Key, Value > *root = root_;
    Node< Key, Value > *node = new Node< Key, Value >(std::make_pair(key, value), nullptr, fake_, fake_, -1);
    while (root->left != fake_ && root->right != fake_)
    {
      if (cmp(key, root->data_)
      {
        root = root->left;
      }
      else
      {
        root = root->right;
      }
    }
    if (cmp(key, root->data))
    {
      if (root->left != fake_)
      {
        root = root->left;
        if (cmp(key, root->data)
        {
          root->left = node;
        }
        else
        {
          root->rigth = node;
        }
      }
      else
      {
        root->left = node;
      }
    }
    else
    {
      if (root->right != fake_)
      {
        root = root->right;
        if (cmp(key, root->data_)
        {
          root->left = node;
        }
        else
        {
          root->right = node;
        }
      }
      else
      {
        root->right = node;
      }
    }
    node->parent = root;
    ++size_;
  }

  template< class Key, class Value, class Cmp >
  size_t BinarySearchTree< Key, Value, Cmp >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class Value, class Cmp >
  bool BinarySearchTree< Key, Value, Cmp >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< class Key, class Value, class Cmp >
  void BinarySearchTree< Key, Value, Cmp >::swap(BinarySearchTree< Key, Value, Cmp > &rhs) noexcept
  {
    std::swap(root_, rhs.root_);
    std::swap(fake_, rhs.fake_);
    std::swap(cmp_, rhs.cmp_);
    std::swap(size_, rhs.size_);
  }

  template< class Key, class Value, class Cmp >
  void BinarySearchTree< Key, Value, Cmp >::clearNodes(Node< Key, Value > *root) noexcept
  {
    if (root != fake_)
    {
      clearNodes(root->left_);
      clearNodes(root->rigth_);
      delete root;
    }
  }

  template< class Key, class Value, class Cmp >
  void BinarySearchTree< Key, Value, Cmp >::clear() noexcept
  {
    Node< Key, Value > *root = root_;
    clearNodes(root);
    delete fake_;
  }
}
#endif

#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP
#include <cstddef>
#include <algorithm>
#include <functional>
#include "node.hpp"

namespace abramov
{
  template< class Key, class Value >
  struct Node;

  template< class Key, class Value, class Cmp = std::less< Key > >
  struct BinarySearchTree
  {
    BinarySearchTree();
    void push(Key key, Value value);
    size_t size() const noexcept;
    bool empty() const noexcept;
    void swap(BinarySearchTree &rhs) noexcept;
    void clear() noexcept;
  private:
    Node< Key, Value > *root_;
    Node< Key, Value > *fake_;
    Cmp cmp_;
    size_t size_;
    friend struct Node< Key, Value >;

    void clearNodes(Node< Key, Value > *root) noexcept;
  };

  template< class Key, class Value, class Cmp >
  BinarySearchTree< Key, Value, Cmp >::BinarySearchTree():
    root_(new Node< Key, Value >),
    fake_(root_),
    cmp_(std::less< Key >()),
    size_(0)
  {}

  template< class Key, class Value, class Cmp >
  void BinarySearchTree< Key, Value, Cmp >::push(Key key, Value value)
  {
    if (size_ == 0)
    {
      std::pair< Key, Value > p(key, value);
      root_ = new Node< Key, Value >(p, Node< Key, Value >{ p, nullptr, fake_, fake_ });
      ++size_;
      return;
    }
    Node< Key, Value > *node = root_;
    while (root_->left != fake_ || root_->rigth != fake_)
    {
      if (cmp(key, root_->data_.first()))
      {
        root_ = root_->left;
      }
      else
      {
        root_ = root_->rigth;
      }
    }
    std::pair< Key, Value > p(key, value);
    Node< Key, Value > *leaf = new Node< Key, Value >(p, node);
    if (cmp(key, root_->data.first()))
    {
      root_->left = leaf;
    }
    else
    {
      root_->rigth = leaf;
    }
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

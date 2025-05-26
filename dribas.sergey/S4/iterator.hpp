#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "avlTree.hpp"

namespace dribas
{
  template <class Key, class T, class Compare> class AVLTree;
  template <class Key, class T> class Node;

  template< class Key, class T, class Compare = std::less< Key > >
  class Iterator
  {
    friend class AVLTree< Key,T, Compare >;
  public:
    using valueType = std::pair< Key, T >;
    using Tree = AVLTree< Key, T, Compare >;
    using Node_t = Node< Key, T >;

    Iterator() noexcept;
    valueType& operator*() noexcept;
    valueType* operator->() noexcept;
    Iterator& operator++() noexcept;
    Iterator operator++(int) noexcept;
    Iterator& operator--() noexcept;
    Iterator operator--(int) noexcept;

    bool operator==(const Iterator& other) const noexcept;
    bool operator!=(const Iterator& other) const noexcept;

  private:
    Node_t* node_;
    const Tree* tree_;
    explicit Iterator(Node< Key, T >* node, const Tree* tree) noexcept;
  };

  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare >::Iterator() noexcept:
    node_(nullptr),
    tree_(nullptr)
  {}

  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare >::Iterator(Node< Key, T >* node, const Tree* tree) noexcept:
    node_(node),
    tree_(tree)
  {}

  template< class Key, class T, class Compare >
  std::pair< Key, T >& Iterator< Key, T, Compare >::operator*() noexcept
  {
    return node_->value;
  }

  template< class Key, class T, class Compare >
  std::pair< Key, T >* Iterator< Key, T, Compare >::operator->() noexcept
  {
    return std::addressof(node_->value);
  }

  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare >& Iterator< Key, T, Compare >::operator++() noexcept
  {
    if (!node_->right->isFake) {
      node_ = node_->right;
      while (!node_->left->isFake) {
        node_ = node_->left;
      }
    } else {
      Node< Key, T >* prev = node_;
      node_ = node_->parent;
      while (node_ && prev == node_->right) {
        prev = node_;
        node_ = node_->parent;
      }
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  Iterator< Key, T, Compare >& Iterator< Key, T, Compare >::operator--() noexcept
  {
    if (!node_->left->isFake) {
      node_ = node_->left;
      while (!node_->right->isFake) {
        node_ = node_->right;
      }
    } else {
      Node< Key, T >* before;
      node_ = node_->parent;
      while (node_ && before == node_->left) {
        before = node_;
        node_ = node_->parent;
      }
    }
    return *this;
  }

  template < class Key, class T, class Compare >
  Iterator< Key, T, Compare > Iterator< Key, T, Compare >::operator--(int) noexcept
  {
    Iterator tmp = *this;
    --(*this);
    return tmp;
  }

  template < class Key, class T, class Compare >
  Iterator< Key, T, Compare > Iterator< Key, T, Compare >::operator++(int) noexcept
  {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  template < class Key, class T, class Compare >
  bool Iterator< Key, T, Compare >::operator==(const Iterator& other) const noexcept
  {
    return node_ == other.node_;
  }

  template < class Key, class T, class Compare >
  bool Iterator< Key, T, Compare >::operator!=(const Iterator& other) const noexcept
  {
    return !(node_ == other.node_);
  }
}

#endif

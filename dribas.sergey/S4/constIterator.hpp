#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "avlTree.hpp"

namespace dribas
{
  template <class Key, class T, class Compare> class Iterator;
  template <class Key, class T, class Compare> class AVLTree;
  template <class Key, class T> class Node;

  template < class Key, class T, class Compare = std::less< Key > >
  class ConstIterator
  {
    friend class AVLTree< Key, T, Compare >;
  public:
    using valueType = std::pair< Key, T >;
    using Tree = AVLTree< Key, T, Compare >;

    ConstIterator() noexcept;
    ConstIterator(const Iterator< Key, T, Compare >&) noexcept;
    const valueType& operator*() const noexcept;
    const valueType* operator->() const noexcept;
    ConstIterator& operator++() noexcept;
    ConstIterator operator++(int) noexcept;
    ConstIterator& operator--() noexcept;
    ConstIterator operator--(int) noexcept;

    bool operator==(const ConstIterator&) const noexcept;
    bool operator!=(const ConstIterator&) const noexcept;

  private:
    const Node< Key, T >* node_;
    const Tree* tree_;
    explicit ConstIterator(const Node< Key, T >*, const Tree*) noexcept;
  };

  template < class Key, class T, class Compare >
  ConstIterator< Key, T, Compare >::ConstIterator(const Iterator< Key, T, Compare >& other) noexcept:
    node_(other.node_), tree_(other.tree_)
  {}

  template < class Key, class T, class Compare >
  ConstIterator< Key, T, Compare >::ConstIterator() noexcept:
    node_(nullptr),
    tree_(nullptr)
  {}

  template < class Key, class T, class Compare >
  ConstIterator<Key, T, Compare>::ConstIterator(const Node<Key, T>* node, const Tree* tree) noexcept:
    node_(node),
    tree_(tree)
  {}

  template < class Key, class T, class Compare >
  const std::pair< Key, T >& ConstIterator< Key, T, Compare >::operator*() const noexcept
  {
    return node_->value;
  }

  template < class Key, class T, class Compare >
  const std::pair< Key, T >* ConstIterator< Key, T, Compare >::operator->() const noexcept
  {
    return std::addressof(node_->value);
  }

  template <class Key, class T, class Compare>
  ConstIterator<Key, T, Compare>& ConstIterator<Key, T, Compare>::operator++() noexcept
  {
    if (!node_->right->isFake) {
      node_ = node_->right;
      while (!node_->left->isFake) {
        node_ = node_->left;
      }
    } else {
      const Node< Key, T >* prev = node_;
      node_ = node_->parent;
      while (node_ && prev == node_->right) {
        prev = node_;
        node_ = node_->parent;
      }
    }
    return *this;
  }

  template <class Key, class T, class Compare>
  ConstIterator<Key, T, Compare>& ConstIterator<Key, T, Compare>::operator--() noexcept
  {
    if (!node_->left->isFake) {
      node_ = node_->left;
      while (!node_->right->isFake) {
        node_ = node_->right;
      }
    } else {
      const Node< Key, T >* before;
      node_ = node_->parent;
      while (node_ && before == node_->left) {
        before = node_;
        node_ = node_->parent;
      } 
    }
    return *this;
  }

  template < class Key, class T, class Compare >
  ConstIterator< Key, T, Compare > ConstIterator< Key, T, Compare >::operator--(int) noexcept
  {
    ConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  template < class Key, class T, class Compare >
  ConstIterator< Key, T, Compare > ConstIterator< Key, T, Compare >::operator++(int) noexcept
  {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  template < class Key, class T, class Compare >
  bool ConstIterator< Key, T, Compare >::operator==(const ConstIterator& other) const noexcept
  {
    return node_ == other.node_;
  }

  template < class Key, class T, class Compare >
  bool ConstIterator< Key, T, Compare >::operator!=(const ConstIterator& other) const noexcept
  {
    return !(node_ == other.node_);
  }
}

#endif

#ifndef TREE_CITER_HPP
#define TREE_CITER_HPP
#include <iterator>
#include "tree-node.hpp"

namespace sveshnikov
{
  template< class Key, class T, class Cmp >
  class AvlTree;

  template< class Key, class T >
  class ConstIter: public std::iterator< bidirectional_iterator_tag, Key, T >
  {
  public:
    using value_t = std::pair< Key, T >;
    ConstIter();
    ConstIter(const ConstIter &rhs) = default;
    ~ConstIter() = default;

    ConstIter &operator=(const ConstIter &rhs) = default;
    ConstIter &operator++() noexcept;
    ConstIter operator++(int) noexcept;
    ConstIter &operator--() noexcept;
    ConstIter operator--(int) noexcept;

    const value_t &operator*() const noexcept;
    const value_t *operator->() const noexcept;

    bool operator!=(const ConstIter &rhs) const noexcept;
    bool operator==(const ConstIter &rhs) const noexcept;

  private:
    const tree_node_t< Key, T > *node_;

    ConstIter(const tree_node_t< Key, T > *node);

    template< class Key, class T, class Cmp >
    friend class AvlTree< class Key, class T, class Cmp >;
  };

  template< class Key, class T >
  ConstIter< Key, T >::ConstIter():
    node_(nullptr)
  {}

  template< class Key, class T >
  ConstIter< Key, T >::ConstIter(const tree_node_t< Key, T > *node):
    node_(node)
  {}

  template< class Key, class T >
  ConstIter< Key, T > &ConstIter< Key, T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    if (node_->right_)
    {
      node_ = node_->right_;
      while (node_->left_)
      {
        node_ = node_->left_;
      }
    }
    else
    {
      while (node_->parent_ && node_ == node_->parent_->left_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return *this;
  }

  template< class Key, class T >
  ConstIter< Key, T > ConstIter< Key, T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    ConstIter result(*this);
    ++(*this);
    return result;
  }

  template< class Key, class T >
  ConstIter< Key, T > &ConstIter< Key, T >::operator--() noexcept
  {
    assert(node_ != nullptr);
    if (node_->left_)
    {
      node_ = node_->left_;
      while (node_->right_)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      while (node_->parent_ && node_ == node_->parent_->left_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return *this;
  }

  template< class Key, class T >
  ConstIter< Key, T > ConstIter< Key, T >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    ConstIter result(*this);
    --(*this);
    return result;
  }

  template< class Key, class T >
  const ConstIter< Key, T >::value_t &ConstIter< Key, T >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< class Key, class T >
  const ConstIter< Key, T >::value_t *ConstIter< Key, T >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< class Key, class T >
  bool ConstIter< Key, T >::operator!=(const ConstIter &rhs) const noexcept
  {
    return node_ != rhs.node_;
  }

  template< class Key, class T >
  bool ConstIter< Key, T >::operator==(const ConstIter &rhs) const noexcept
  {
    return node_ == rhs.node_;
  }
}

#endif

#ifndef TREE_ITER_HPP
#define TREE_ITER_HPP
#include <iterator>
#include "tree-node.hpp"

namespace sveshnikov
{
  template< class Key, class T, class Cmp >
  class AvlTree;

  template< class Key, class T >
  class Iter: public std::iterator< bidirectional_iterator_tag, Key, T >
  {
  public:
    using value_t = std::pair< Key, T >;
    Iter();
    Iter(const Iter &rhs) = default;
    ~Iter() = default;

    Iter &operator=(const Iter &rhs) = default;
    Iter &operator++() noexcept;
    Iter operator++(int) noexcept;
    Iter &operator--() noexcept;
    Iter operator--(int) noexcept;

    const value_t &operator*() const noexcept;
    value_t &operator*() noexcept;
    const value_t *operator->() const noexcept;
    value_t *operator->() noexcept;

    bool operator!=(const Iter &rhs) const noexcept;
    bool operator==(const Iter &rhs) const noexcept;

  private:
    const tree_node_t< Key, T > *node_;

    Iter(const tree_node_t< Key, T > *node);

    template< class Key, class T, class Cmp >
    friend class AvlTree< class Key, class T, class Cmp >;
  };

  template< class Key, class T >
  Iter< Key, T >::Iter():
    node_(nullptr)
  {}

  template< class Key, class T >
  Iter< Key, T >::Iter(const tree_node_t< Key, T > *node):
    node_(node)
  {}

  template< class Key, class T >
  Iter< Key, T > &Iter< Key, T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    if (node_->right_->height_ != 0)
    {
      node_ = node_->right_;
      while (node_->left_->height_ != 0)
      {
        node_ = node_->left_;
      }
    }
    else
    {
      auto current = node_;
      while (current->parent_ && current != current->parent_->left_)
      {
        current = current->parent_;
      }
      if (current->parent_)
      {
        node_ = current->parent_;
      }
      else
      {
        node_ = node_->right_;
      }
    }
    return *this;
  }

  template< class Key, class T >
  Iter< Key, T > Iter< Key, T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    Iter result(*this);
    ++(*this);
    return result;
  }

  template< class Key, class T >
  Iter< Key, T > &Iter< Key, T >::operator--() noexcept
  {
    assert(node_ != nullptr);
    if (node_->height_ == 0)
    {
      node_ = node_->parent_;
      return *this;
    }
    if (node_->left_->height_ != 0)
    {
      node_ = node_->left_;
      while (node_->right_->height_ != 0)
      {
        node_ = node_->right_;
      }
    }
    else
    {
      while (node_->parent_ && node_ != node_->parent_->right_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return *this;
  }

  template< class Key, class T >
  Iter< Key, T > Iter< Key, T >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    Iter result(*this);
    --(*this);
    return result;
  }

  template< class Key, class T >
  const Iter< Key, T >::value_t &Iter< Key, T >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< class Key, class T >
  Iter< Key, T >::value_t &Iter< Key, T >::operator*() noexcept
  {
    return const_cast< value_t & >(static_cast< const Iter< Key, T > & >(*this).operator*());
  }

  template< class Key, class T >
  const Iter< Key, T >::value_t *Iter< Key, T >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< class Key, class T >
  Iter< Key, T >::value_t *Iter< Key, T >::operator->() noexcept
  {
    return const_cast< value_t * >(static_cast< const Iter< Key, T > * >(this)->operator->())
  }

  template< class Key, class T >
  bool Iter< Key, T >::operator!=(const Iter &rhs) const noexcept
  {
    return node_ != rhs.node_;
  }

  template< class Key, class T >
  bool Iter< Key, T >::operator==(const Iter &rhs) const noexcept
  {
    return node_ == rhs.node_;
  }
}

#endif

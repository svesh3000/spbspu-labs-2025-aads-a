#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include "treeNode.hpp"

namespace finaev
{
  template< class key, class value, class Cmp >
  class AVLtree;

  template< class key, class value, class Cmp >
  class treeIterator: public std::iterator< std::bidirectional_iterator_tag, std::pair< key, value > >
  {
    friend class AVLtree< key, value, Cmp >;
  public:
    using this_t = treeIterator< key, value, Cmp >;
    treeIterator();
    ~treeIterator() = default;
    treeIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;
    this_t & operator++() noexcept;
    this_t operator++(int) noexcept;
    this_t & operator--() noexcept;
    this_t operator--(int) noexcept;
    std::pair< key, value > & operator*() const;
    std::pair< key, value > * operator->() const;
    bool operator==(const this_t &) const noexcept;
    bool operator!=(const this_t &) const noexcept;
  private:
    treeNode< key, value >* node_;
    explicit treeIterator(treeNode< key, value >*);
  };

  template< class key, class value, class Cmp >
  treeIterator< key, value, Cmp >::treeIterator():
    node_(nullptr)
  {}

  template< class key, class value, class Cmp >
  treeIterator< key, value, Cmp >::treeIterator(treeNode< key, value >* node):
    node_(node)
  {}

  template< class key, class value, class Cmp >
  treeIterator< key, value, Cmp >& treeIterator< key, value, Cmp >::operator++() noexcept
  {
    if (node_->right)
    {
      node_ = node_->right;
      while (node_->left)
      {
        node_ = node_->left;
      }
    }
    else
    {
      auto parent = node_->parent;
      while (parent && node_ == parent->right)
      {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  template< class key, class value, class Cmp >
  treeIterator< key, value, Cmp > treeIterator< key, value, Cmp >::operator++(int) noexcept
  {
    treeIterator< key, value, Cmp > temp = *this;
    ++(*this);
    return temp;
  }

  template< class key, class value, class Cmp >
  treeIterator< key, value, Cmp >& treeIterator< key, value, Cmp >::operator--() noexcept
  {
    if (node_->left)
    {
      node_ = node_->left;
      while (node_->right)
      {
        node_ = node_->right;
      }
    }
    else
    {
      auto parent = node_->parent;
      while (parent && node_ == parent->left)
      {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  template< class key, class value, class Cmp >
  treeIterator< key, value, Cmp > treeIterator< key, value, Cmp >::operator--(int) noexcept
  {
    treeIterator< key, value, Cmp > result = *this;
    --(*this);
    return result;
  }

  template< class key, class value, class Cmp >
  std::pair< key, value >& treeIterator< key, value, Cmp >::operator*() const
  {
    return node_->data;
  }

  template< class key, class value, class Cmp >
  std::pair< key, value >* treeIterator< key, value, Cmp >::operator->() const
  {
    return std::addressof(node_->data);
  }

  template< class key, class value, class Cmp >
  bool treeIterator< key, value, Cmp >::operator==(const this_t& other) const noexcept
  {
    return node_ == other.node_;
  }

  template< class key, class value, class Cmp >
  bool treeIterator< key, value, Cmp >::operator!=(const this_t& other) const noexcept
  {
    return !(other == *this);
  }
}

#endif

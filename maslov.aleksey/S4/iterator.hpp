#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <iterator>
#include "node.hpp"

namespace maslov
{
  template< typename Key, typename T, typename Cmp >
  struct BiTree;

  template< typename Key, typename T, typename Cmp >
  struct TreeIterator final: public std::iterator< std::bidirectional_iterator_tag, std::pair< const Key, T > >
  {
    friend struct BiTree< Key, T, Cmp >;
   public:
    using thisT = TreeIterator< Key, T, Cmp >;

    TreeIterator();
    TreeIterator(const thisT &) = default;
    ~TreeIterator() = default;
    thisT & operator=(const thisT &) = default;
    thisT & operator++();
    thisT operator++(int);
    std::pair< const Key, T > & operator*();
    std::pair< const Key, T > * operator->();
    bool operator!=(const thisT &) const;
    bool operator==(const thisT &) const;
   private:
    BiTreeNode< Key, T > * node_;
    explicit TreeIterator(BiTreeNode< Key, T > * node);
  };

  template< typename Key, typename T, typename Cmp >
  TreeIterator< Key, T, Cmp >::TreeIterator():
    node_(nullptr)
  {}

  template< typename Key, typename T, typename Cmp >
  TreeIterator< Key, T, Cmp >::TreeIterator(BiTreeNode< Key, T > * node):
    node_(node)
  {}

  template< typename Key, typename T, typename Cmp >
  typename TreeIterator< Key, T, Cmp >::thisT & TreeIterator< Key, T, Cmp >::operator++()
  {
    assert(node_ != nullptr);
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
      auto * parent = node_->parent;
      while (parent && node_ == parent->right)
      {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  template< typename Key, typename T, typename Cmp >
  typename TreeIterator< Key, T, Cmp >::thisT TreeIterator< Key, T, Cmp >::operator++(int)
  {
    assert(node_ != nullptr);
    thisT tmp(*this);
    ++(*this);
    return tmp;
  }

  template< typename Key, typename T, typename Cmp >
  std::pair< const Key, T > & TreeIterator< Key, T, Cmp >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename Key, typename T, typename Cmp >
  std::pair< const Key, T > * TreeIterator< Key, T, Cmp >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename Key, typename T, typename Cmp >
  bool TreeIterator< Key, T, Cmp >::operator!=(const thisT & rhs) const
  {
    return node_ != rhs.node_;
  }

  template< typename Key, typename T, typename Cmp >
  bool TreeIterator< Key, T, Cmp >::operator==(const thisT & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename Key, typename T, typename Cmp >
  struct TreeConstIterator final: public std::iterator< std::bidirectional_iterator_tag, const std::pair< const Key, T > >
  {
    friend struct BiTree< Key, T, Cmp >;
   public:
    using thisT = TreeConstIterator< Key, T, Cmp >;

    TreeConstIterator();
    TreeConstIterator(const thisT &) = default;
    ~TreeConstIterator() = default;
    thisT & operator=(const thisT &) = default;
    thisT & operator++();
    thisT operator++(int);
    const std::pair< const Key, T > & operator*() const;
    const std::pair< const Key, T > * operator->() const;
    bool operator==(const thisT & rhs) const;
    bool operator!=(const thisT & rhs) const;
   private:
    BiTreeNode< Key, T > * node_;
    explicit TreeConstIterator(BiTreeNode< Key, T > * node);
  };
  
  template< typename Key, typename T, typename Cmp >
  TreeConstIterator< Key, T, Cmp >::TreeConstIterator():
    node_(nullptr)
  {}

  template< typename Key, typename T, typename Cmp >
  TreeConstIterator< Key, T, Cmp >::TreeConstIterator(BiTreeNode< Key, T > * node):
    node_(node)
  {}

  template< typename Key, typename T, typename Cmp >
  typename TreeConstIterator< Key, T, Cmp >::thisT & TreeConstIterator< Key, T, Cmp >::operator++()
  {
    assert(node_ != nullptr);
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
      auto* parent = node_->parent;
      while (parent && node_ == parent->right)
      {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }

  template< typename Key, typename T, typename Cmp >
  typename TreeConstIterator< Key, T, Cmp >::thisT TreeConstIterator< Key, T, Cmp >::operator++(int)
  {
    assert(node_ != nullptr);
    thisT tmp(*this);
    ++(*this);
    return tmp;
  }

  template< typename Key, typename T, typename Cmp >
  const std::pair< const Key, T > & TreeConstIterator< Key, T, Cmp >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename Key, typename T, typename Cmp >
  const std::pair< const Key, T > * TreeConstIterator< Key, T, Cmp >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename Key, typename T, typename Cmp >
  bool TreeConstIterator< Key, T, Cmp >::operator!=(const thisT & rhs) const
  {
    return node_ != rhs.node_;
  }

  template< typename Key, typename T, typename Cmp >
  bool TreeConstIterator< Key, T, Cmp >::operator==(const thisT & rhs) const
  {
    return node_ == rhs.node_;
  }
}

#endif

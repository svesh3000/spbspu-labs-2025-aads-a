#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <memory>
#include <iterator>
#include <cstddef>
#include "node.hpp"

namespace maslov
{
  template< typename T >
  
  struct FwdListIterator
  {
    using this_t = FwdListIterator< T >;
    using value_type = T;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    FwdListIterator();
    FwdListIterator(FwdListNode< T > *);
    FwdListIterator(const this_t &) = default;
    ~FwdListIterator() = default;
    this_t & operator=(const this_t &) = default;

    T & operator*();
    T * operator->();

    this_t & operator++();
    this_t operator++(int);

    bool operator!=(const this_t &) const;
    bool operator==(const this_t &) const;
   private:
    FwdListNode< T > * node_;
  };

  template< typename T >
  FwdListIterator< T >::FwdListIterator():
    node_(nullptr)
  {}

  template< typename T >
  FwdListIterator< T >::FwdListIterator(FwdListNode< T > * node):
    node_(node)
  {}

  template< typename T >
  T & FwdListIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T * FwdListIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  typename FwdListIterator< T >::this_t & FwdListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  typename FwdListIterator< T >::this_t FwdListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp = *this;
    ++(*this);
    return temp;
  }

  template< typename T >
  bool FwdListIterator< T >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool FwdListIterator< T >::operator!=(const this_t & rhs) const
  {
    return node_ != rhs.node_;
  }

  template < typename T >
  struct FwdListConstIterator
  {
    using this_t = FwdListConstIterator< T >;
    using value_type = T;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;

    FwdListConstIterator();
    FwdListConstIterator(const this_t &) = default;
    FwdListConstIterator(FwdListNode< T > * node);
    ~FwdListConstIterator() = default;
    this_t & operator=(const this_t &) = default;

    this_t & operator++();
    this_t operator++(int);

    const T & operator*() const;
    const T * operator->() const;

    bool operator==(const this_t &) const;
    bool operator!=(const this_t &) const;
   private:
    FwdListNode< T > * node_;
  };

  template< typename T >
  FwdListConstIterator< T >::FwdListConstIterator():
    node_(nullptr)
  {}

  template< typename T >
  FwdListConstIterator< T >::FwdListConstIterator(FwdListNode< T > * node):
    node_(node)
  {}

  template< typename T >
  const T & FwdListConstIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  const T * FwdListConstIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  typename FwdListConstIterator< T >::this_t & FwdListConstIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  typename FwdListConstIterator< T >::this_t FwdListConstIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp = *this;
    ++(*this);
    return temp;
  }

  template< typename T >
  bool FwdListConstIterator< T >::operator==(const this_t & rhs) const
  {
    return node_ == rhs.node_;
  }

  template< typename T >
  bool FwdListConstIterator< T >::operator!=(const this_t & rhs) const
  {
    return node_ != rhs.node_;
  }
}
#endif

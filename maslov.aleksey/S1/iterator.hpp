#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <memory>
#include "node.hpp"

namespace maslov
{
  template< typename T >
  struct FwdListIterator
  {
    using this_t = FwdListIterator< T >;

    FwdListIterator();
    FwdListIterator(FwdListNode< T > *);
    ~FwdListIterator() = default;
    FwdListIterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;

    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;

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
  const T & FwdListIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T & FwdListIterator< T >::operator*()
  {
    return const_cast< T & >(static_cast< const FwdListIterator & >(*this).operator*());
  }

  template< typename T >
  const T * FwdListIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T >
  T * FwdListIterator< T >::operator->()
  {
    return const_cast< T * >(static_cast< const FwdListIterator & >(*this).operator->());
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
}
#endif

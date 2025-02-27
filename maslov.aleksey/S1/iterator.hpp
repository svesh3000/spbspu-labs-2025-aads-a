#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "node.hpp"

namespace maslov
{
  template< typename T >
  struct FwdListIterator
  {
    using this_t = FwdListNode< T >;

    FwdListIterator();
    FwdListIterator(this_t *);
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
  FwdListIterator< T >::FwdListIterator(FwdListIterator< T >::this_t * node):
    node_(node)
  {}

  template< typename T >
  const T & FwdListIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
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
    return std::addressof(node_->data_);
  }

  template< typename T >
  T * FwdListIterator< T >::operator->()
  {
    return const_cast< T * >(static_cast< const FwdListIterator & >(*this).operator->());
  }

  template< typename T >
  FwdListIterator< T >::this_t & FwdListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node = node->next;
    return *this;
  }

  template< typename T >
  FwdListIterator< T >::this_t FwdListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t temp = *this;
    ++(*this);
    return temp;
  }

  template< typename T >
  bool FwdListIterator< T >::operator==(const FwdListIterator< T >::this_t & other) const
  {
    return node_ == other.node_;
  }

  template< typename T >
  bool FwdListIterator< T >::operator!=(const FwdListIterator< T >::this_t & other) const
  {
    return node_ != other.node_;
  }
}
#endif

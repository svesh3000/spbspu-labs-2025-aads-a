#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace kiselev
{
  template< typename T >
  class ConstIterator
  {
  public:

    ConstIterator(): node_(nullptr) {}
    ConstIterator(Node< T >* node): node_(node) {}

    ConstIterator< T >& operator++();
    ConstIterator< T > operator++(int);

    ConstIterator< T >& operator--();
    ConstIterator< T > operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const ConstIterator< T >&) const;
    bool operator!=(const ConstIterator< T >&) const;

  private:

    const Node< T >* node_;

  };

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    ConstIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator--()
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    ConstIterator< T > result(*this);
    --(*this);
    return result;
  }

  template< typename T >
  const T& ConstIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T >
  const T* ConstIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T >
  bool ConstIterator< T >::operator==(const ConstIterator< T >& it) const
  {
    return node_ == it.node_;
  }

  template< typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T >& it) const
  {
    return !(it == *this);
  }

}
#endif

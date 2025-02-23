#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP
#include <cstddef>
#include <iterator>
#include <type_traits>
#include "iterator.hpp"
#include "node.hpp"

namespace kiselev
{
  template< typename T >
  class List;
  template< typename T >
  class ConstIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
  public:

    ConstIterator(): node_(nullptr) {}
    ConstIterator(Node< T >* node): node_(node) {}
    ConstIterator(Iterator< T > it): node_(it.node_) {}

    ConstIterator< T >& operator++();
    ConstIterator< T > operator++(int);

    ConstIterator< T >& operator--();
    ConstIterator< T > operator--(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const ConstIterator< T >&) const;
    bool operator!=(const ConstIterator< T >&) const;


  private:

    Node< T >* node_;

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

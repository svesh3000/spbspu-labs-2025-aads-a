#ifndef CITERATOR_HPP
#define CITERATOR_HPP

#include <cassert>
#include <iterator>
#include "node.hpp"

namespace duhanina
{
  template < typename T >
  struct constIterator: public std::iterator<std::bidirectional_iterator_tag, T>
  {
  public:
    constIterator();
    constIterator(const Node< T >* node);
    ~constIterator() = default;

    constIterator< T >& operator++();
    constIterator< T > operator++(int);

    const T& operator*() const;
    const T* operator->() const;

    bool operator==(const constIterator< T >&) const;
    bool operator!=(const constIterator< T >&) const;

  private:
    const Node<T>* node_;
  };

  template< typename T >
  constIterator< T >::constIterator():
    node_(nullptr)
  {}

  template< typename T >
  constIterator< T >::constIterator(const Node< T >* node):
    node_(node)
  {}

  template< typename T >
  constIterator< T >& constIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  constIterator< T > constIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    constIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  const T& constIterator< T >::operator*() const
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T >
  const T* constIterator< T >::operator->() const
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T >
  bool constIterator< T >::operator==(const constIterator< T >& it) const
  {
    return node_ == it.node_;
  }

  template< typename T >
  bool constIterator< T >::operator!=(const constIterator< T >& it) const
  {
    return !(it == *this);
  }
}

#endif

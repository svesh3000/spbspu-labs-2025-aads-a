#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
#include <memory>
#include "node.hpp"
namespace kiselev
{
  template< typename T>
  class Iterator
  {
  public:

    Iterator(): node_(nullptr) {}
    Iterator(const Iterator< T >&) = default;
    Iterator(Node< T >* node): node_(node) {}
    ~Iterator() = default;
    Iterator< T >& operator=(const Iterator< T >&) = default;

    Iterator< T >& operator++();
    Iterator< T >& operator++(int);

    T& operator*();
    T* operator->();

    bool operator==(const Iterator< T >&) const;
    bool operator!=(const Iterator< T >&) const;

  private:

    Node< T >* node_;

  };

  template< typename T >
  Iterator< T >& Iterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template< typename T >
  Iterator< T >& Iterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    Iterator< T > result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  T& Iterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template< typename T >
  T* Iterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T >
  bool Iterator< T >::operator==(const Iterator< T >& it) const
  {
    return node_ == it.node_;
  }

  template< typename T >
  bool Iterator< T >::operator!=(const Iterator< T >& it) const
  {
    return !(it == *this);
  }

}
#endif

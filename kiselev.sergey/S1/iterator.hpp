#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <cstddef>
#include "list.hpp"
namespace kiselev
{
  template< typename T>
  class Iterator
  {
  public:

    using iter = Iterator< T >;

    Iterator(): node_(nullptr) {}
    Iterator(const iter&) = default;
    Iterator(Node< T >* node): node_(node) {}
    ~Iterator() = default;
    iter& operator=(const iter&) = default;

    iter& operator++();
    iter& operator++(int);
    iter& operator+=(size_t);

    T& operator*();
    T* operator->();

    bool operator==(const iter&) const;
    bool operator!=(const iter&) const;

  private:

    Node< T >* node_;

  };

  template< typename T >
  typename Iterator< T >::iter& Iterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T >
  typename Iterator< T >::iter& Iterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    iter result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  typename Iterator< T >::iter& Iterator< T >::operator+=(size_t i)
  {
    for (size_t j = 0; j < i; ++j)
    {
      ++(*this);
    }
    return *this;
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
  bool Iterator< T >::operator==(const iter& it) const
  {
    return node_ == it.node_;
  }

  template< typename T >
  bool Iterator< T >::operator!=(const iter& it) const
  {
    return !(it == *this);
  }

}
#endif

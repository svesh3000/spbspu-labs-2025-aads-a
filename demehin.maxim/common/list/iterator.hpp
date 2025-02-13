#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"

namespace demehin
{
  template< typename T >
  struct ListIterator
  {
  public:
    using this_t = ListIterator< T >;

    ListIterator();
    ListIterator(const this_t&) = default;
    ListIterator(Node< T >* node);
    ~ListIterator() = default;
    this_t& operator=(const this_t&) = default;

    this_t& operator++();
    this_t& operator++(int);

    this_t& operator--();
    this_t& operator--(int);

    T& operator*();
    T* operator->();

    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

  private:
    Node< T >* node_;
  };

  template< typename T >
  ListIterator< T >::ListIterator():
    node_(nullptr)
  {}

  template< typename T >
  ListIterator< T >::ListIterator(Node< T >* node):
    node_(node)
  {}

  template< typename T >
  ListIterator< T >::this_t& ListIterator< T >::operator++()
  {
    assert(node_ != nullptr);
    node = node_->next_;
    return *this;
  }

  template< typename T >
  ListIterator< T >::this_t& ListIterator< T >::operator++(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  ListIterator< T >::this_t& ListIterator< T >::operator--()
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return *this;
  }

  template< typename T >
  ListIterator< T >::this_t& ListIterator< T >::operator--(int)
  {
    assert(node_ != nullptr);
    this_t result(*this);
    --(*this);
    return result;
  }

  template< typename T >
  T& ListIterator< T >::operator*()
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T >
  T* ListIterator< T >::operator->()
  {
    assert(node_ != nullptr);
    return std::adressof(node_->data);
  }

}

#endif

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cassert>
#include <iterator>
#include "node.hpp"

namespace kushekbaev
{
  template< typename T >
  struct Iterator final: public std::iterator< std::forward_iterator_tag, T >
  {
    using this_t = Iterator< T >;
    Node< T >* node;

    Iterator() noexcept;
    Iterator(Node< T >*) noexcept;
    Iterator(const this_t&) = default;
    ~Iterator() = default;

    this_t& operator=(const this_t&) = default;
    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;

    T& operator*() const noexcept;
    T* operator -> () const noexcept;

    bool operator!=(const this_t&) const noexcept;
    bool operator==(const this_t&) const noexcept;

    Node< T >* getNode() const noexcept;

    private:
      Node< T >* node_;
  };

  template< typename T >
  Iterator< T >::Iterator() noexcept:
    node_(nullptr)
  {}

  template< typename T >
  Iterator< T >::Iterator(Node< T > * node) noexcept:
    node_(node)
  {}

  template< typename T >
  typename Iterator< T >::this_t & Iterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_ -> next_;
    return *this;
  }

  template< typename T >
  typename Iterator< T >::this_t Iterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template< typename T >
  T & Iterator< T >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_ -> data_;
  }

  template< typename T >
  T * Iterator< T >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node -> data_);
  }

  template< typename T >
  bool Iterator< T >::operator!=(const this_t& other) const noexcept
  {
    return !(other == *this);
  }

  template< typename T >
  bool Iterator< T >::operator==(const this_t& other) const noexcept
  {
    return node_ == other.node;
  }

  template< typename T >
  Node< T > * Iterator< T >::getNode() const noexcept
  {
    return node_;
  }
}

#endif

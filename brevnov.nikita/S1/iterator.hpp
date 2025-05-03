#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "node.hpp"
#include <cassert>
#include <iterator>
namespace brevnov
{
  template< typename T, bool isConst >
  class Iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    using ref = std::conditional_t< isConst, const T&, T& >;
    using point = std::conditional_t< isConst, const T*, T* >;
    Iterator();
    Iterator();
    template< bool OtherisConst, std::enable_if_t< isConst && !OtherisConst, int > = 0 >
    Iterator(const Iterator< T, OtherisConst >& other): node_(other.node_) {}
    template< bool OtherisConst, std::enable_if_t< isConst && !OtherisConst, int > = 0 >
    Iterator< T, isConst >& operator=(const Iterator< T, OtherisConst >& other);

    Iterator< T, isConst >& operator++() noexcept;
    Iterator< T, isConst > operator++(int) noexcept;

    Iterator< T, isConst >& operator--() noexcept;
    Iterator< T, isConst > operator--(int) noexcept;

    ref operator*() const noexcept;
    point operator->() const noexcept;

    bool operator==(const Iterator< T, isConst >&) const noexcept;
    bool operator!=(const Iterator< T, isConst >&) const noexcept;

  private:
    Node< T >* node_;
    explicit Iterator(Node< T >* node);
    friend class Iterator< T,  !isConst >;
    friend class List< T >;
  };

  template< typename T, bool isConst >
  Iterator< T, isConst>::Iterator():
    node_(nullptr)
  {}

  template< typename T, bool isConst >
  Iterator< T, isConst >::Iterator(Node< T >* node):
    node_(node)
  {}

  template< typename T, bool isConst >
  template< bool OtherisConst, std::enable_if_t< isConst && !OtherisConst, int > >
  Iterator< T, isConst >& Iterator< T, isConst >::operator=(const Iterator< T, OtherisConst >& other)
  {
    node_ = other.node_;
    return *this;
  }

  template< typename T, bool isConst >
  Iterator< T, isConst >& Iterator< T, isConst >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next;
    return *this;
  }

  template< typename T, bool isConst >
  Iterator< T, isConst > Iterator< T, isConst >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    Iterator< T, isConst > result(*this);
    ++(*this);
    return result;
  }

  template< typename T, bool isConst >
  Iterator< T, isConst >& Iterator< T, isConst >::operator--() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->prev;
    return *this;
  }

  template< typename T, bool isConst >
  Iterator< T, isConst > Iterator< T, isConst >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    Iterator< T, isConst > result(*this);
    --(*this);
    return result;
  }

  template< typename T, bool isConst >
  typename Iterator< T, isConst >::ref Iterator< T, isConst >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template< typename T, bool isConst >
  typename Iterator< T, isConst >::point Iterator< T, isConst >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }

  template< typename T, bool isConst >
  bool Iterator< T, isConst >::operator==(const Iterator< T, isConst >& it) const noexcept
  {
    return node_ == it.node_;
  }

  template< typename T, bool isConst >
  bool Iterator< T, isConst >::operator!=(const Iterator< T, isConst >& it) const noexcept
  {
    return !(it == *this);
  }

}

#endif

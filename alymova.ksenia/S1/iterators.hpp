#ifndef ITERATORS_HPP
#define ITERATORS_HPP
#include <cassert>
#include "list.hpp"
#include "listNode.hpp"

namespace alymova
{
  template< typename T >
  struct Iterator
    public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    Iterator();
    Iterator(ListNode< T >* node);
    Iterator< T >& operator++() noexcept;
    Iterator< T > operator++(int) noexcept;
    Iterator< T >& operator--() noexcept;
    Iterator< T > operator--(int) noexcept;
    bool operator==(const Iterator< T >& other) noexcept;
    bool operator!=(const Iterator< T >& other) noexcept;
    T& operator*() noexcept;
    T* operator->() noexcept;
  private:
    friend class List< T >;
    ListNode< T >* node_;
  };
  template< typename T >
  struct ConstIterator
    public std::iterator<std::bidirectional_iterator_tag, T >
  {
  public:
    ConstIterator();
    ConstIterator(ListNode< T >* node);
    ConstIterator< T >& operator++() noexcept;
    ConstIterator< T > operator++(int) noexcept;
    ConstIterator< T >& operator--() noexcept;
    ConstIterator< T > operator--(int) noexcept;
    bool operator==(const ConstIterator< T >& other) noexcept;
    bool operator!=(const ConstIterator< T >& other) noexcept;
    const T& operator*() noexcept;
    const T* operator->() noexcept;
  private:
    friend class List< T >;
    const ListNode< T >* node_;
  };
  
  template< typename T >
  Iterator< T >::Iterator():
    node_(nullptr)
  {}
  template< typename T >
  Iterator< T >::Iterator(ListNode< T >* node):
    node_(node)
  {}
  template< typename T >
  Iterator< T >& Iterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }
  template< typename T >
  Iterator< T > Iterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    Iterator< T > old = *this;
    node_ = node_->next_;
    return old;
  }
  template< typename T >
  Iterator< T >& Iterator< T >::operator--() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return *this;
  }
  template< typename T >
  Iterator< T > Iterator< T >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    Iterator< T > old = *this;
    node_ = node_->prev_;
    return old;
  }
  template< typename T >
  bool Iterator< T >::operator==(const Iterator< T >& other) noexcept
  {
    return node_ == other.node_;
  }
  template< typename T >
  bool Iterator< T >::operator!=(const Iterator< T >& other) noexcept
  {
    return node_ != other.node_;
  }
  template< typename T >
  T& Iterator< T >::operator*() noexcept
  {
    assert(node_ != nullptr);
    return node_->data_;
  }
  template< typename T >
  T* Iterator< T >::operator->() noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }

  template< typename T >
  ConstIterator< T >::ConstIterator():
    node_(nullptr)
  {}
  template< typename T >
  ConstIterator< T >::ConstIterator(ListNode< T >* node):
    node_(node)
  {}
  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }
  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    ConstIterator< T > old = *this;
    node_ = node_->next_;
    return old;
  }
  template< typename T >
  ConstIterator< T >& ConstIterator< T >::operator--() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->prev_;
    return *this;
  }
  template< typename T >
  ConstIterator< T > ConstIterator< T >::operator--(int) noexcept
  {
    assert(node_ != nullptr);
    ConstIterator< T > old = *this;
    node_ = node_->prev_;
    return old;
  }
  template< typename T >
  bool ConstIterator< T >::operator==(const ConstIterator< T >& other) noexcept
  {
    return node_ == other.node_;
  }
  template< typename T >
  bool ConstIterator< T >::operator!=(const ConstIterator< T >& other) noexcept
  {
    return node_ != other.node_;
  }
  template< typename T >
  const T& ConstIterator< T >::operator*() noexcept
  {
    assert(node_ != nullptr);
    return node_->data_;
  }
  template< typename T >
  const T* ConstIterator< T >::operator->() noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }
}
#endif

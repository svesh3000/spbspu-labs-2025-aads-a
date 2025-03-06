#ifndef CONSTITARATOR_HPP
#define CONSTITARATOR_HPP

#include "node.hpp"

namespace dribas
{
  template< class T >
  class ConstItarator
  {
  public:
    using citer = ConstItarator< T >;

    ConstItarator() noexcept;
    ConstItarator(Node< T >* head) noexcept;

    citer& operator++() noexcept;
    citer& operator--() noexcept;
    citer operator++(int) noexcept;
    citer operator--(int) noexcept;

    bool operator==(const citer& other) const noexcept;
    bool operator!=(const citer& other) const noexcept;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;

  private:
    Node< T >* head_;
  };

  template< class T >
  bool ConstItarator< T >::operator==(const citer& other) const noexcept
  {
    return head_->data_ == other.head_->data_;
  }

  template< class T >
  bool ConstItarator< T >::operator!=(const citer& other) const noexcept
  {
    return !(*this == other);
  }

  template< class T >
  ConstItarator< T >::ConstItarator() noexcept:
    head_(nullptr)
  {}

  template< class T >
  ConstItarator< T >::ConstItarator(Node< T >* head) noexcept:
    head_(head)
  {}

  template< class T >
  typename ConstItarator< T >::citer& ConstItarator< T >::operator++() noexcept
  {
    head_ = head_->next_;
    return *this;
  }

  template< class T >
  typename ConstItarator< T >::citer ConstItarator< T >::operator++(int) noexcept
  {
    citer decr(*this);
    ++(*this);
    return decr;
  }

  template< class T >
  typename ConstItarator< T >::citer& ConstItarator< T >::operator--() noexcept
  {
    head_ = head_->prev_;
    return *this;
  }

  template< class T >
  typename ConstItarator< T >::citer ConstItarator< T >::operator--(int) noexcept
  {
    citer precr(*this);
    --(*this);
    return precr;
  }

  template< class T >
  const T& ConstItarator< T >::operator*() const noexcept
  {
    return node_->data;
  }

  template< typename T >
  const T* ConstItarator< T >::operator->() const noexcept
  {
    return std::addressof(node_->data);
  }

}


#endif
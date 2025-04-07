#ifndef ITARATOR_HPP
#define ITARATOR_HPP

#include "node.hpp"
#include "list.hpp"

namespace dribas
{
  template< class T > 
  class List;

  template< class T, bool ifConst >
  class Itarator final: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
  public:
    using iter = Itarator< T, ifConst >;

    Itarator() noexcept;
    Itarator(Node< T >* head) noexcept;
    Itarator(const iter&) = default;

    iter& operator=(const iter&) = default;
    iter& operator++() noexcept;
    iter& operator--() noexcept;
    iter operator++(int) noexcept;
    iter operator--(int) noexcept;

    bool operator==(const iter& other) const noexcept;
    bool operator!=(const iter& other) const noexcept;

    const T& operator*() const noexcept;
    const T* operator->() const noexcept;
  private:
    Node< T >* head_;
  };

  template< class T, bool ifConst >
  bool Itarator< T,  ifConst >::operator==(const iter& other) const noexcept
  {
    return head_ == other.head_;
  }

  template< class T, bool ifConst >
  bool Itarator< T,  ifConst >::operator!=(const iter& other) const noexcept
  {
    return !(*this == other);
  }

  template< class T, bool ifConst >
  Itarator< T,  ifConst >::Itarator() noexcept:
    head_(nullptr)
  {}

  template< class T, bool ifConst >
  Itarator< T,  ifConst >::Itarator(Node< T >* head) noexcept:
    head_(head)
  {}

  template< class T, bool ifConst >
  typename Itarator< T,  ifConst >::iter& Itarator< T,  ifConst >::operator++() noexcept
  {
    head_ = head_->next_;
    return *this;
  }

  template< class T, bool ifConst >
  typename Itarator< T,  ifConst >::iter Itarator< T,  ifConst >::operator++(int) noexcept
  {
    iter decr(*this);
    ++(*this);
    return decr;
  }

  template< class T, bool ifConst >
  typename Itarator< T,  ifConst >::iter& Itarator< T,  ifConst >::operator--() noexcept
  {
    head_ = head_->prev_;
    return *this;
  }

  template< class T, bool ifConst >
  typename Itarator< T,  ifConst >::iter Itarator< T,  ifConst >::operator--(int) noexcept
  {
    iter precr(*this);
    --(*this);
    return precr;
  }

  template< class T, bool ifConst >
  const T& Itarator< T,  ifConst >::operator*() const noexcept
  {
    return head_->data_;
  }

  template< class T, bool ifConst >
  const T* Itarator< T,  ifConst >::operator->() const noexcept
  {
    return std::addressof(head_->data);
  }
}

#endif

#ifndef FWD_ITERATOR_HPP
#define FWD_ITERATOR_HPP
#include <memory>
#include "fwdlist-node.hpp"

namespace sveshnikov
{
  template < typename T >
  class FwdIterator
  {
  public:
    FwdIterator();
    FwdIterator(node_t< T > *node);
    FwdIterator(const FwdIterator< T > &) = default;
    ~FwdIterator() = default;
    FwdIterator< T > &operator=(const FwdIterator< T > &) = default;
    FwdIterator< T > &operator++() noexcept;
    FwdIterator< T > operator++(int) noexcept;
    T &operator*() noexcept;
    const T &operator*() const noexcept;
    T *operator->() noexcept;
    const T *operator->() const noexcept;
    bool operator!=(const FwdIterator< T > &) const noexcept;
    bool operator==(const FwdIterator< T > &) const noexcept;

  private:
    node_t< T > *node_;
  };

  template < typename T >
  FwdIterator< T >::FwdIterator():
    node_(nullptr)
  {}

  template < typename T >
  FwdIterator< T >::FwdIterator(node_t< T > *node):
    node_(node)
  {}

  template < typename T >
  FwdIterator< T > &FwdIterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template < typename T >
  FwdIterator< T > FwdIterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    FwdIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template < typename T >
  bool FwdIterator< T >::operator==(const FwdIterator< T > &rhs) const noexcept
  {
    return node_ == rhs.node_;
  }

  template < typename T >
  bool FwdIterator< T >::operator!=(const FwdIterator< T > &rhs) const noexcept
  {
    return !(rhs == *this);
  }

  template < typename T >
  T &FwdIterator< T >::operator*() noexcept
  {
    return const_cast< T & >(static_cast< const FwdIterator< T > & >(*this).operator*());
  }

  template < typename T >
  const T &FwdIterator< T >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < typename T >
  T *FwdIterator< T >::operator->() noexcept
  {
    return const_cast< T * >(static_cast< const FwdIterator< T > * >(this)->operator->());
  }

  template < typename T >
  const T *FwdIterator< T >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }
}

#endif

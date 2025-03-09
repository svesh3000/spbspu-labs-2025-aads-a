#ifndef CONST_FWDITERATOR_HPP
#define CONST_FWDITERATOR_HPP
#include "fwdlist-node.hpp"

namespace sveshnikov
{
  template < typename T >
  class FwdIterator
  {
  public:
    FwdIterator();
    ~FwdIterator() = default;
    FwdIterator(const FwdIterator< T > &) = default;
    FwdIterator< T > &operator=(const FwdIterator< T > &) = default;
    FwdIterator< T > &operator++() noexcept;
    FwdIterator< T > operator++(int) noexcept;
    const T &operator*() const noexcept;
    const T *operator->() const noexcept;
    bool operator!=(const FwdIterator< T > &) const noexcept;
    bool operator==(const FwdIterator< T > &) const noexcept;

  private:
    using this_t = FwdIterator< T >;
    node_t< T > *node_;
  };

  template < typename T >
  FwdIterator< T >::FwdIterator():
    node_(nullptr)
  {}

  template < typename T >
  FwdIterator< T >::this_t &FwdIterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->node;
    return *this;
  }

  template < typename T >
  FwdIterator< T >::this_t FwdIterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    this_t result(*this);
    ++(*this);
    return result;
  }

  template < typename T >
  bool FwdIterator< T >::operator==(const this_t &rhs) const noexcept
  {
    return node_ == rhs.node_;
  }

  template < typename T >
  bool FwdIterator< T >::operator!=(const this_t &rhs) const noexcept
  {
    return !(rhs == *this);
  }

  template < typename T >
  const T &FwdIterator< T >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data;
  }

  template < typename T >
  const T *FwdIterator< T >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data);
  }
}

#endif

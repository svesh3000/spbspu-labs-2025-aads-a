#ifndef FWD_CITERATOR_HPP
#define FWD_CITERATOR_HPP
#include <memory>
#include "fwdlist-node.hpp"

namespace sveshnikov
{
  template < typename T >
  class ConstFwdIterator
  {
  public:
    ConstFwdIterator();
    ConstFwdIterator(const node_t< T > *node);
    ConstFwdIterator(const ConstFwdIterator< T > &) = default;
    ~ConstFwdIterator() = default;
    ConstFwdIterator< T > &operator=(const ConstFwdIterator< T > &) = default;
    ConstFwdIterator< T > &operator++() noexcept;
    ConstFwdIterator< T > operator++(int) noexcept;
    const T &operator*() const noexcept;
    const T *operator->() const noexcept;
    bool operator!=(const ConstFwdIterator< T > &) const noexcept;
    bool operator==(const ConstFwdIterator< T > &) const noexcept;

  private:
    const node_t< T > *node_;
  };

  template < typename T >
  ConstFwdIterator< T >::ConstFwdIterator():
    node_(nullptr)
  {}

  template < typename T >
  ConstFwdIterator< T >::ConstFwdIterator(const node_t< T > *node):
    node_(node)
  {}

  template < typename T >
  ConstFwdIterator< T > &ConstFwdIterator< T >::operator++() noexcept
  {
    assert(node_ != nullptr);
    node_ = node_->next_;
    return *this;
  }

  template < typename T >
  ConstFwdIterator< T > ConstFwdIterator< T >::operator++(int) noexcept
  {
    assert(node_ != nullptr);
    ConstFwdIterator< T > result(*this);
    ++(*this);
    return result;
  }

  template < typename T >
  bool ConstFwdIterator< T >::operator==(const ConstFwdIterator< T > &rhs) const noexcept
  {
    return node_ == rhs.node_;
  }

  template < typename T >
  bool ConstFwdIterator< T >::operator!=(const ConstFwdIterator< T > &rhs) const noexcept
  {
    return !(rhs == *this);
  }

  template < typename T >
  const T &ConstFwdIterator< T >::operator*() const noexcept
  {
    assert(node_ != nullptr);
    return node_->data_;
  }

  template < typename T >
  const T *ConstFwdIterator< T >::operator->() const noexcept
  {
    assert(node_ != nullptr);
    return std::addressof(node_->data_);
  }
}

#endif

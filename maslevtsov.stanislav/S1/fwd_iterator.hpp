#ifndef FWD_ITERATOR_HPP
#define FWD_ITERATOR_HPP

#include <iterator>
#include "fwd_list_node.hpp"

namespace maslevtsov {
  template< typename T >
  class FwdIterator final: public std::iterator< std::forward_iterator_tag, int >
  {
  public:
    using this_t = FwdIterator< T >;

    FwdIterator() = default;
    FwdIterator(const this_t& rhs);
    explicit FwdIterator(FwdListNode< T >* node);
    ~FwdIterator() = default;

    this_t& operator=(const FwdIterator& rhs);
    this_t& operator++();
    this_t& operator++(int);
    T& operator*() const noexcept;
    T* operator->() const noexcept;
    bool operator==(const this_t& rhs) const;
    bool operator!=(const this_t& rhs) const;

  private:
    FwdListNode< T >* node_;
  };
}

template< typename T >
maslevtsov::FwdIterator< T >::FwdIterator(const this_t& rhs):
  node_(rhs.node_)
{}

template< typename T >
maslevtsov::FwdIterator< T >::FwdIterator(FwdListNode< T >* node):
  node_(node)
{}

template< typename T >
typename maslevtsov::FwdIterator< T >::this_t& maslevtsov::FwdIterator< T >::operator=(const FwdIterator& rhs)
{
  node_ = rhs.node_;
  return *this;
}

template< typename T >
typename maslevtsov::FwdIterator< T >::this_t& maslevtsov::FwdIterator< T >::operator++()
{
  node_ = node_->next_;
  return *this;
}

template< typename T >
typename maslevtsov::FwdIterator< T >::this_t& maslevtsov::FwdIterator< T >::operator++(int)
{
  FwdIterator< T > result(*this);
  ++(*this);
  return result;
}

template< typename T >
T& maslevtsov::FwdIterator< T >::operator*() const noexcept
{
  return node_->data_;
}

template< typename T >
T* maslevtsov::FwdIterator< T >::operator->() const noexcept
{
  return std::addressof(node_->data_);
}

template< typename T >
bool maslevtsov::FwdIterator< T >::operator==(const this_t& rhs) const
{
  return node_ == rhs.node_;
}

template< typename T >
bool maslevtsov::FwdIterator< T >::operator!=(const this_t& rhs) const
{
  return !(*this == rhs);
}

#endif

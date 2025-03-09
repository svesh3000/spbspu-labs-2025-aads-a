#ifndef FWDLIST_RING_HPP
#define FWDLIST_RING_HPP
#include "fwdlist-node.hpp"
#include "fwditerator.hpp"
#include "const-fwditerator.hpp"

namespace sveshnikov
{
  template < typename T >
  class FwdList
  {
  public:
    explicit FwdList();
    FwdIterator< T > begin() noexcept;
    ConstFwdIterator< T > begin() const noexcept;
    FwdIterator< T > end() noexcept;
    ConstFwdIterator< T > end() const noexcept;
    ConstFwdIterator< T > cbegin() const noexcept;
    ConstFwdIterator< T > cend() const noexcept;
    T &front();
    const T &front() const;
    bool empty() const noexcept;
    size_t getSize() const noexcept;
    void push_front(const T &val);
    void push_front(T &&val);
    void pop_front();
    void swap(FwdList< T > &fwdlst);
    void clear() noexcept;

  private:
    node_t< T > *head_;
    node_t< T > *tail_;
    size_t size_;
  };

  template < typename T >
  FwdList< T >::FwdList():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template < typename T >
  FwdIterator< T > FwdList< T >::begin() noexcept
  {
    return FwdIterator< T >(head_);
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::begin() const noexcept
  {
    return ConstFwdIterator< T >(head_);
  }

  template < typename T >
  FwdIterator< T > FwdList< T >::end() noexcept
  {
    return FwdIterator< T >(tail_);
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::end() const noexcept
  {
    return ConstFwdIterator< T >(tail_);
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::cbegin() const noexcept
  {
    return ConstFwdIterator< T >(head_);
  }

  template < typename T >
  ConstFwdIterator< T > FwdList< T >::cend() const noexcept
  {
    return ConstFwdIterator< T >(tail_);
  }
}

#endif

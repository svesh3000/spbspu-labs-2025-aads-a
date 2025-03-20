#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include "node.hpp"

namespace shramko
{
  template< typename T >
  class List;

  template< typename T, bool is_const >
  class FwdListIterator final: public std::iterator< std::forward_iterator_tag, int >
  {
  public:
    FwdListIterator() noexcept = default;
    FwdListIterator(const this_t&) noexcept = default;
    ~FwdListIterator() = default;

    this_t& operator++() noexcept
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }

    this_t operator++(int) noexcept
    {
      assert(node_ != nullptr);
      FwdListIterator< T, is_const > res = *this;
      ++(*this);
      return res;
    }

    typename std::conditional< is_const, const T&, T& >::type operator*()const noexcept
    {
      return node_->data_
    }

    typename std::conditional< is_const, const T *, T * >::type operator->() const noexcept
    {
      return std::addressof(node_->data_);
    }

    typename std::conditional< is_const, const T *, T * >::type operator->() const noexcept
    {
      return std::addressof(node_->data_);
    }

    bool operator!=(const Iterator & rhs) const noexcept
    {
      return !(*this == rhs);
    }

  private:
    friend class List< T >;
    FwdListNode< T >* node_;
    FwdListIterator(FwdListNode< T >* node) noexcept:
      node_(node)
    {}
  };
}

#endif
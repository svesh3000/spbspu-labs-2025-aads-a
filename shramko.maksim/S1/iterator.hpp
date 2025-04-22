#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <type_traits>
#include <cassert>
#include "node.hpp"

namespace shramko
{
  template< typename T >
  class FwdList;

  template< typename T, bool is_const >
  class FwdListIterator : public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    using this_t = FwdListIterator<T, is_const>;
    using node_type = typename std::conditional<is_const, const FwdListNode<T>, FwdListNode<T>>::type;
    using value_type = typename std::conditional<is_const, const T, T>::type;
    
    FwdListIterator() noexcept = default;
    FwdListIterator(node_type* node) noexcept : node_(node) {}
    FwdListIterator(const this_t&) noexcept = default;
    
    this_t& operator=(const this_t&) noexcept = default;
    
    value_type& operator*() const noexcept
    {
      assert(node_ != nullptr);
      return node_->data_;
    }

    value_type* operator->() const noexcept
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_);
    }

    this_t& operator++() noexcept
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }

    this_t operator++(int) noexcept
    {
      this_t tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const this_t& rhs) const noexcept
    {
      return node_ == rhs.node_;
    }

    bool operator!=(const this_t& rhs) const noexcept
    {
      return !(*this == rhs);
    }

  private:
    friend class FwdList<T>;
    node_type* node_ = nullptr;
  };
}

#endif
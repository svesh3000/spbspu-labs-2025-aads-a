#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <iterator>
#include "FwdListNode.hpp"

namespace shramko
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ConstIterator
  {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    ConstIterator() noexcept: node_(nullptr) {}

    explicit ConstIterator(ListNode< T >* node) noexcept: node_(node) {}

    ConstIterator& operator++() noexcept
    {
      if (node_ != nullptr)
      {
        node_ = node_->nextPtr;
      }
      return *this;
    }

    ConstIterator operator++(int)
    {
      ConstIterator temp = *this;
      ++(*this);
      return temp;
    }

    reference operator*() const
    {
      if (node_ == nullptr)
      {
        throw std::logic_error("Iterator at end or invalid");
      }
      return node_->dataValue;
    }

    pointer operator->() const
    {
      if (node_ == nullptr)
      {
        throw std::logic_error("Iterator at end or invalid");
      }
      return &(node_->dataValue);
    }

    bool operator==(const ConstIterator& other) const noexcept
    {
      return node_ == other.node_;
    }

    bool operator!=(const ConstIterator& other) const noexcept
    {
      return !(*this == other);
    }

  private:
    friend class ForwardList< T >;
    ListNode< T >* node_;
  };
}

#endif

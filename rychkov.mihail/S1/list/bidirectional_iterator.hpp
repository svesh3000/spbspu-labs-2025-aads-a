#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>
#include <type_traits>

namespace rychkov
{
  template< class T >
  struct List;
  template< class T >
  struct node_t
  {
    T data;
    node_t* prev = nullptr;
    node_t* next = nullptr;
  };

  template< class T, bool isConst, bool isReversed >
  class BidirectionalIterator
  {
  public:
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;

    BidirectionalIterator() noexcept:
      node_(nullptr)
    {}
    template< bool isConst1 = isConst >
    BidirectionalIterator(typename std::enable_if_t< isConst && isConst1,
            BidirectionalIterator< value_type, false, isReversed > > rhs) noexcept:
      node_(rhs.node_)
    {}

    bool operator==(BidirectionalIterator rhs) const noexcept
    {
      return node_ == rhs.node_;
    }
    bool operator!=(BidirectionalIterator rhs) const noexcept
    {
      return !(*this == rhs);
    }

    BidirectionalIterator& operator++() noexcept
    {
      if (isReversed)
      {
        node_ = node_->prev;
      }
      else
      {
        node_ = node_->next;
      }
      return *this;
    }
    BidirectionalIterator operator++(int) noexcept
    {
      BidirectionalIterator< T, isConst, isReversed > temp = *this;
      ++(*this);
      return temp;
    }
    BidirectionalIterator& operator--() noexcept
    {
      if (isReversed)
      {
        node_ = node_->next;
      }
      else
      {
        node_ = node_->prev;
      }
      return *this;
    }
    BidirectionalIterator operator--(int) noexcept
    {
      BidirectionalIterator< T, isConst, isReversed > temp = *this;
      --(*this);
      return temp;
    }

    template< bool isConst1 = isConst >
    typename std::enable_if_t< isConst && isConst1, reference > operator*() noexcept
    {
      return node_->data;
    }
    const reference operator*() const noexcept
    {
      return node_->data;
    }
    template< bool isConst1 = isConst >
    typename std::enable_if_t< isConst && isConst1, pointer > operator->() noexcept
    {
      return std::addressof(node_->data);
    }
    const value_type* operator->() const noexcept
    {
      return std::addressof(node_->data);
    }
  private:
    friend class rychkov::List< T >;
    friend class BidirectionalIterator< value_type, true, isReversed >;
    node_t< T >* node_;
    BidirectionalIterator(node_t< T >* node) noexcept:
      node_(node)
    {}
  };
}

#endif

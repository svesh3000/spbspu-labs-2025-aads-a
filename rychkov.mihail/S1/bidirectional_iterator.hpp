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
    node_t* next;
    node_t* prev;
  };

  template< class T, bool isConst, bool isReversed >
  class BidirectionalIterator
  {
  public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;

    BidirectionalIterator() noexcept:
      node_(nullptr)
    {}

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
    }
    BidirectionalIterator operator--(int) noexcept
    {
      BidirectionalIterator< T, isConst, isReversed > temp = *this;
      --(*this);
      return temp;
    }

    typename std::enable_if< isConst, reference >::type operator*() noexcept
    {
      return node_->data;
    }
    const reference operator*() const noexcept
    {
      return node_->data;
    }
    typename std::enable_if< isConst, pointer >::type operator->() noexcept
    {
      return std::adressof(node_->data);
    }
    const pointer operator->() const noexcept
    {
      return std::adressof(node_->data);
    }
  private:
    friend class rychkov::List< T >;
    node_t* node_;
    BidirectionalIterator(node_t* node) noexcept:
      node_(node)
    {}
  };
}

#endif

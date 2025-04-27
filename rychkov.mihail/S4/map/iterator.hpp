#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include <type_traits.hpp>
#include "node.hpp"

namespace rychkov
{
  template< class Value, size_t N, bool isConst, bool isReversed >
  class MapIterator
  {
  public:
    using node_type = MapNode< Value, N >;
    static constexpr size_t node_capacity = N;

    using difference_type = ptrdiff_t;
    using value_type = typename node_type::value_type;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;

    MapIterator() noexcept:
      node_(nullptr),
      pointed_(0)
    {};
    template< bool isConst1 = isConst >
    MapIterator(typename std::enable_if_t< isConst && isConst1,
          MapIterator< Value, N, false, isReversed > > rhs) noexcept:
      node_(rhs.node_),
      pointed_(rhs.pointed_)
    {}

    bool operator==(MapIterator rhs) const noexcept
    {
      return (node_ == rhs.node_) && (pointed_ == rhs.pointed_);
    }
    bool operator!=(MapIterator rhs) const noexcept
    {
      return !operator==(rhs);
    }

    MapIterator& operator++() noexcept
    {
      isReversed ? shift_left() : shift_right();
      return *this;
    }
    MapIterator operator++(int) noexcept
    {
      MapIterator temp = *this;
      operator++();
      return temp;
    }
    MapIterator& operator--() noexcept
    {
      isReversed ? shift_right() : shift_left();
      return *this;
    }
    MapIterator operator--(int) noexcept
    {
      MapIterator temp = *this;
      operator--();
      return temp;
    }

    template< bool isConst1 = isConst >
    typename std::enable_if_t< !isConst && !isConst1, value_type& > operator*() noexcept
    {
      return node_->operator[](pointed_);
    }
    const value_type& operator*() const noexcept
    {
      return node_->operator[](pointed_);
    }

    template< bool isConst1 = isConst >
    typename std::enable_if_t< !isConst && !isConst1, value_type* > operator->() noexcept
    {
      return std::addressof(node_->operator[](pointed_));
    }
    const value_type* operator->() const noexcept
    {
      return std::addressof(node_->operator[](pointed_));
    }
  private:
    template< class K, class M, class C, size_t N1 >
    friend class Map;
    friend class MapIterator< Value, N, true, isReversed >;

    using node_size_type = typename node_type::size_type;
    node_type* node_;
    node_size_type pointed_;

    MapIterator(node_type* node, node_size_type pointed) noexcept:
      node_(node),
      pointed_(pointed)
    {}
    void shift_left() noexcept;
    void shift_right() noexcept;
    void move_up() noexcept;
  };
}

template< class Value, size_t N, bool isConst, bool isReversed >
void rychkov::MapIterator< Value, N, isConst, isReversed >::shift_left() noexcept
{
  if (node_->isfake() || !node_->isleaf())
  {
    node_ = (node_->isfake() ? node_->children[0] : node_->children[pointed_]);
    for (; !node_->isleaf(); node_ = node_->children[node_->size()])
    {}
    pointed_ = node_->size() - 1;
    return;
  }
  if (pointed_ > 0)
  {
    pointed_--;
  }
  else
  {
    node_type* prev = node_;
    node_ = node_->parent;
    for (; !node_->isfake() && (node_->children[0] == prev); prev = node_, node_ = node_->parent)
    {}
    for (pointed_ = node_->size(); pointed_ > 0; pointed_--)
    {
      if (node_->children[pointed_] == prev)
      {
        break;
      }
    }
  }
}
template< class Value, size_t N, bool isConst, bool isReversed >
void rychkov::MapIterator< Value, N, isConst, isReversed >::shift_right() noexcept
{
  if (node_->isfake() || !node_->isleaf())
  {
    node_ = (node_->isfake() ? node_->children[0] : node_->children[pointed_ + 1]);
    for (; !node_->isleaf(); node_ = node_->children[0])
    {}
    pointed_ = 0;
    return;
  }
  if (pointed_ + 1 < node_->size())
  {
    pointed_++;
  }
  else
  {
    node_type* prev = node_;
    node_ = node_->parent;
    for (; !node_->isfake() && (node_->children[node_->size()] == prev); prev = node_, node_ = node_->parent)
    {}
    for (pointed_ = 0; pointed_ < node_->size(); pointed_++)
    {
      if (node_->children[pointed_] == prev)
      {
        break;
      }
    }
  }
}
template< class Value, size_t N, bool isConst, bool isReversed >
void rychkov::MapIterator< Value, N, isConst, isReversed >::move_up() noexcept
{
  node_type* prev = node_;
  node_ = node_->parent;
  for (pointed_ = 0; pointed_ < node_->size(); pointed_++)
  {
    if (node_->children[pointed_] == prev)
    {
      break;
    }
  }
}

#endif

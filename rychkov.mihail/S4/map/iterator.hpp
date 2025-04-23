#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "declaration.hpp"
#include <iterator>

template< class Key, class Mapped, size_t N, bool isConst, bool isReversed >
class rychkov::MapIterator
{
public:
  using difference_type = ptrdiff_t;
  using value_type = std::pair< const Key, Mapped >;
  using pointer = value_type*;
  using reference = value_type&;
  using iterator_category = std::bidirectional_iterator_tag;

  MapIterator() noexcept:
    node_(nullptr),
    pointed_(0)
  {};
  template< bool isConst1 = isConst >
  MapIterator(typename std::enable_if_t< isConst && isConst1,
        MapIterator< Key, Mapped, N, false, isReversed > > rhs) noexcept:
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
    isReversed ? shiftLeft() : shiftRight();
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
    isReversed ? shiftLeft() : shiftRight();
    return *this;
  }
  MapIterator operator--(int) noexcept
  {
    MapIterator temp = *this;
    operator++();
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
  friend class MapIterator< Key, Mapped, N, true, isReversed >;

  static constexpr size_t node_capacity = N;
  using node_type = MapNode< Key, Mapped, N >;
  using node_size_type = typename node_type::size_type;
  node_type* node_;
  node_size_type pointed_;

  MapIterator(node_type* node, node_size_type pointed) noexcept:
    node_(node),
    pointed_(pointed)
  {}
  void shiftLeft() noexcept;
  void shiftRight() noexcept;
};

template< class Key, class Mapped, size_t N, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Mapped, N, isConst, isReversed >::shiftLeft() noexcept
{
  if (node_->child(pointed_) == nullptr)
  {
    if (pointed_ > 0)
    {
      pointed_--;
    }
    else
    {
      node_type* prev = node_;
      node_ = node_->parent();
      for (; !node_->isFake() && (node_->child(0) == prev); node_ = node_->parent())
      {}
      for (pointed_ = node_->size(); pointed_ > 0; pointed_--)
      {
        if (node_->child(pointed_) == prev)
        {
          break;
        }
      }
    }
    return;
  }
  node_ = node_->child(pointed_);
  for (; node_->child(node_->size()) != nullptr; node_ = node_->child(node_->size()))
  {}
}
template< class Key, class Mapped, size_t N, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Mapped, N, isConst, isReversed >::shiftRight() noexcept
{
  if (node_->child(pointed_ + 1) == nullptr)
  {
    if (pointed_ + 1 < node_->size())
    {
      pointed_++;
    }
    else
    {
      node_type* prev = node_;
      node_ = node_->parent();
      for (; !node_->isFake() && (node_->child(node_->size()) == prev); node_ = node_->parent())
      {}
      for (pointed_ = 0; pointed_ < node_->size(); pointed_++)
      {
        if (node_->child(pointed_) == prev)
        {
          break;
        }
      }
    }
    return;
  }
  node_ = node_->child(pointed_ + 1);
  for (; node_->child(0) != nullptr; node_ = node_->child(0))
  {}
}

#endif

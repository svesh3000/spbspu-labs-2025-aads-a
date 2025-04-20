#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "declaration.hpp"
#include <iterator>

template< class Key, class Mapped, size_t N, bool isConst, bool isReversed >
class rychkov::MapIterator
{
public:
  using difference_type = ptrdiff_t;
  using value_type = std::pair< Key, Mapped >;
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

  using node_type = MapNode< Key, Mapped, N >;
  node_type* node_;
  typename node_type::size_type pointed_;

  MapIterator(node_type* node, typename node_type::size_type pointed) noexcept:
    node_(node),
    pointed_(pointed)
  {}
  void shiftLeft() noexcept;
  void shiftRight() noexcept;
};

template< class Key, class Mapped, size_t N, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Mapped, N, isConst, isReversed >::shiftLeft() noexcept
{
  /*if (node_->parent != nullptr)
  {
    if (node_->left != nullptr)
  }
  else
  {
    if (node_->left == nullptr)
    {
      node_ = node_->parent;
      isLeftActive_ = (node_ == nullptr) || (node_->second_part == nullptr);
      return;
    }
    node_ = node_->left;
  }
  while (node_->second_part == nullptr ? node_->second_part->right != nullptr : node_->right != nullptr)
  {
    node_ = node_->second_part == nullptr ? node_->second_part->right : node_->right;
  }*/
}
template< class Key, class Mapped, size_t N, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Mapped, N, isConst, isReversed >::shiftRight() noexcept
{
  /*if (!isLeftActive_)
  {
    if (node_->second_part->right == nullptr)
    {
      node_ = node_->parent;
      isLeftActive_ = (node_ == nullptr) || (node_->second_part == nullptr);
      return;
    }
    node_ = node_->right;
  }
  else
  {
    if (node_->right == nullptr)
    {
      isLeftActive_ = true;
      return;
    }
    node_ = node_->left;
  }
  while (node_->left == nullptr)
  {
    node_ = node_->left;
  }*/
}

#endif

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "declaration.hpp"
#include <iterator>

template< class Key, class Value, bool isConst, bool isReversed >
class rychkov::MapIterator
{
public:
  using difference_type = ptrdiff_t;
  using value_type = std::pair< Key, Value >;
  using pointer = value_type*;
  using reference = value_type&;
  using iterator_category = std::bidirectional_iterator_tag;

  MapIterator() noexcept:
    node_(nullptr)
  {}

  template< class = std::enable_if_t< !isConst > >
  MapIterator(MapIterator< Key, Value, false, isReversed > rhs) noexcept:
    node_(rhs.node_)
  {}

  bool operator==(MapIterator rhs) const noexcept
  {
    return node_ == rhs.node_;
  }
  bool operator!=(MapIterator rhs) const noexcept
  {
    return !(*this == rhs);
  }

  MapIterator& operator++() noexcept
  {
    if (isReversed)
    {
      shiftLeft();
    }
    else
    {
      shiftRight();
    }
    return *this;
  }
  MapIterator operator++(int) noexcept
  {
    MapIterator temp = *this;
    ++(*this);
    return temp;
  }
  MapIterator& operator--() noexcept
  {
    if (isReversed)
    {
      shiftRight();
    }
    else
    {
      shiftLeft();
    }
    return *this;
  }
  MapIterator operator--(int) noexcept
  {
    MapIterator temp = *this;
    --(*this);
    return temp;
  }

  template< class = std::enable_if_t< !isConst > >
  value_type& operator*() noexcept
  {
    return node_->data;
  }
  const value_type& operator*() const noexcept
  {
    return node_->data;
  }
  template< class = std::enable_if_t< !isConst > >
  value_type* operator->() noexcept
  {
    return std::addressof(node_->data);
  }
  const value_type* operator->() const noexcept
  {
    return std::addressof(node_->data);
  }
private:
  template< class K, class V, class C >
  friend class Map;
  friend class MapIterator< Key, Value, true, isReversed >;

  using node_type = MapNode< Key, Value >;
  node_type* node_;

  MapIterator(node_type* data) noexcept:
    node_(data)
  {}
  void shiftLeft() noexcept;
  void shiftRight() noexcept;
};

template< class Key, class Value, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Value, isConst, isReversed >::shiftLeft() noexcept
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
template< class Key, class Value, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Value, isConst, isReversed >::shiftRight() noexcept
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

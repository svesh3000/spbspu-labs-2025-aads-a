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
    node_(nullptr),
    prev_(nullptr),
    isLeftActive_(true)
  {}

  template< class = std::enable_if_t< !isConst > >
  MapIterator(MapIterator< Key, Value, false, isReversed > rhs) noexcept:
    node_(rhs.node_),
    prev_(rhs.prev_),
    isLeftActive_(rhs.isLeftActive_)
  {}

  bool operator==(MapIterator rhs) const noexcept
  {
    return (node_ == rhs.node_) && (isLeftActive_ == rhs.isLeftActive_);
  }
  bool operator!=(MapIterator rhs) const noexcept
  {
    return !(*this == rhs);
  }

  MapIterator& operator++() noexcept
  {
    if (isReversed)
    {
      prev_ = node_;
      shiftLeft();
    }
    else
    {
      prev_ = node_;
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
      if (node_ == nullptr)
      {
        node_ = prev_;
      }
      else
      {
        shiftRight();
      }
      prev_ = nullptr;
    }
    else
    {
      if (node_ == nullptr)
      {
        node_ = prev_;
      }
      else
      {
        shiftLeft();
      }
      prev_ = nullptr;
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
    if (isLeftActive_)
    {
      return node_->data;
    }
    return node_->second_part->data;
  }
  const value_type& operator*() const noexcept
  {
    if (isLeftActive_)
    {
      return node_->data;
    }
    return node_->second_part->data;
  }
  template< class = std::enable_if_t< !isConst > >
  value_type* operator->() noexcept
  {
    if (isLeftActive_)
    {
      return std::addressof(node_->data);
    }
    return std::addressof(node_->second_part->data);
  }
  const value_type* operator->() const noexcept
  {
    if (isLeftActive_)
    {
      return std::addressof(node_->data);
    }
    return std::addressof(node_->second_part->data);
  }
private:
  template< class K, class V, class C >
  friend class Map;
  friend class MapIterator< Key, Value, true, isReversed >;

  using node_type = MapLeftNode< Key, Value >;
  node_type* node_;
  node_type* prev_;
  bool isLeftActive_;

  MapIterator(node_type* data, node_type* prev, bool isLeftActive) noexcept:
    node_(data),
    prev_(prev),
    isLeftActive_(isLeftActive)
  {}
  void shiftLeft() noexcept;
  void shiftRight() noexcept;
};

template< class Key, class Value, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Value, isConst, isReversed >::shiftLeft() noexcept
{
  if (!isLeftActive_)
  {
    if (node_->right == nullptr)
    {
      isLeftActive_ = false;
      return;
    }
    node_ = node_->right;
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
  }
}
template< class Key, class Value, bool isConst, bool isReversed >
void rychkov::MapIterator< Key, Value, isConst, isReversed >::shiftRight() noexcept
{
  if (!isLeftActive_)
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
  }
}

#endif

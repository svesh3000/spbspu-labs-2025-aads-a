#ifndef CONSTRUCT_DESTRUCT_HPP
#define CONSTRUCT_DESTRUCT_HPP

#include "declaration.hpp"

template< class Key, class Value, class Compare >
rychkov::Map< Key, Value, Compare >::Map()
    noexcept(std::is_nothrow_default_constructible< value_compare >::value):
  fake_left_(nullptr),
  fake_right_(nullptr),
  fake_parent_(nullptr),
  fake_second_part_(nullptr),
  size_(0),
  comp_()
{}
template< class Key, class Value, class Compare >
rychkov::Map< Key, Value, Compare >::Map(Map&& rhs)
    noexcept(std::is_nothrow_move_constructible< value_compare >::value):
  fake_left_(std::exchange(rhs.fake_left_, nullptr)),
  fake_right_(nullptr),
  fake_parent_(std::exchange(rhs.fake_parent_, nullptr)),
  fake_second_part_(nullptr),
  size_(std::exchange(rhs.size_, 0)),
  comp_(std::move(rhs.comp_))
{}
template< class Key, class Value, class Compare >
rychkov::Map< Key, Value, Compare >&
    rychkov::Map< Key, Value, Compare >::operator=(Map&& rhs) noexcept(noexcept(swap(std::declval< Map >())))
{
  Map temp = std::move(*this);
  swap(rhs);
  return *this;
}
template< class Key, class Value, class Compare >
rychkov::Map< Key, Value, Compare >::~Map()
{
  clear();
}
template< class Key, class Value, class Compare >
void rychkov::Map< Key, Value, Compare >::swap(Map& rhs) noexcept(is_nothrow_swappable_v< value_type >)
{
  std::swap(fake_left_, rhs.fake_left_);
  std::swap(fake_parent_, rhs.fake_parent_);
  std::swap(size_, rhs.size_);
  std::swap(comp_, rhs.comp_);
}
template< class Key, class Value, class Compare >
void rychkov::Map< Key, Value, Compare >::clear()
{
  while (fake_left_)
  {
    if (fake_left_->left != nullptr)
    {
      fake_left_ = fake_left_->left;
    }
    else if (fake_left_->right != nullptr)
    {
      fake_left_ = fake_left_->right;
    }
    else if (fake_left_->second_part != nullptr)
    {
      if (fake_left_->second_part->right != nullptr)
      {
        fake_left_ = fake_left_->second_part->right;
      }
      else
      {
        delete fake_left_->second_part;
        fake_left_->second_part = nullptr;
      }
    }
    else
    {
      node_type* temp = fake_left_;
      fake_left_ = fake_left_->parent;
      delete temp;
    }
  }
}

#endif

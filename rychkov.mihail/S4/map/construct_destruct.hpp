#ifndef CONSTRUCT_DESTRUCT_HPP
#define CONSTRUCT_DESTRUCT_HPP

#include "declaration.hpp"

template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >::Map()
    noexcept(std::is_nothrow_default_constructible< value_compare >::value):
  comp_(),
  cached_begin_(fake_root()),
  cached_rbegin_(fake_root()),
  size_(0),
  fake_parent_(nullptr),
  fake_children_{nullptr},
  fake_size_(0)
{}
template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >::Map(Map&& rhs)
    noexcept(std::is_nothrow_move_constructible< value_compare >::value):
  comp_(std::move(rhs.comp_)),
  cached_begin_(std::exchange(rhs.cached_begin_, rhs.fake_root())),
  cached_rbegin_(std::exchange(rhs.cached_rbegin_, rhs.fake_root())),
  size_(std::exchange(rhs.size_, 0)),
  fake_parent_(std::exchange(rhs.fake_parent_, nullptr)),
  fake_children_{std::exchange(rhs.fake_children_[0], nullptr)},
  fake_size_(0)
{
  if (size_ == 0)
  {
    cached_begin_ = fake_root();
    cached_rbegin_ = cached_begin_;
  }
}
template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >&
    rychkov::Map< Key, Value, Compare, N >::operator=(Map&& rhs) noexcept(noexcept(swap(std::declval< Map >())))
{
  Map temp = std::move(*this);
  swap(rhs);
  return *this;
}
template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >::Map(std::initializer_list< value_type > init):
  Map(init.begin(), init.end())
{}
template< class Key, class Value, class Compare, size_t N >
template< class InputIt >
rychkov::Map< Key, Value, Compare, N >::Map(InputIt from, InputIt to):
  Map()
{
  for (; from != to; ++from)
  {
    emplace(*from);
  }
}
template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >::~Map()
{
  clear();
}
template< class Key, class Value, class Compare, size_t N >
void rychkov::Map< Key, Value, Compare, N >::swap(Map& rhs) noexcept(is_nothrow_swappable_v< value_compare >)
{
  std::swap(comp_, rhs.comp_);
  std::swap(cached_begin_, rhs.cached_begin_);
  std::swap(cached_rbegin_, rhs.cached_rbegin_);
  std::swap(size_, rhs.size_);
  std::swap(fake_children_[0], rhs.fake_children_[0]);
  if (size_ == 0)
  {
    cached_begin_ = fake_root();
    cached_rbegin_ = cached_begin_;
  }
  if (rhs.size_ == 0)
  {
    rhs.cached_begin_ = fake_root();
    rhs.cached_rbegin_ = rhs.cached_begin_;
  }
}
template< class Key, class Value, class Compare, size_t N >
void rychkov::Map< Key, Value, Compare, N >::clear()
{
  destroy_subtree(fake_children_[0]);
  delete fake_children_[0];
  fake_children_[0] = nullptr;
}
template< class Key, class Value, class Compare, size_t N >
void rychkov::Map< Key, Value, Compare, N >::destroy_subtree(node_type* node)
{
  if (node == nullptr)
  {
    return;
  }
  for (node_size_type i = 0; i <= node->size(); i++)
  {
    node_type* child = node->children[i];
    destroy_subtree(child);
    delete child;
  }
}

#endif

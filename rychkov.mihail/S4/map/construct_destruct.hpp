#ifndef CONSTRUCT_DESTRUCT_HPP
#define CONSTRUCT_DESTRUCT_HPP

#include "declaration.hpp"

template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >::Map()
    noexcept(std::is_nothrow_default_constructible< value_compare >::value):
  fake_parent_(nullptr),
  fake_children_{},
  size_(0),
  comp_()
{}
template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >::Map(Map&& rhs)
    noexcept(std::is_nothrow_move_constructible< value_compare >::value):
  fake_parent_(std::exchange(rhs.fake_parent_, nullptr)),
  fake_children_(rhs.fake_children_),
  size_(std::exchange(rhs.size_, 0)),
  comp_(std::move(rhs.comp_))
{}
template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >&
    rychkov::Map< Key, Value, Compare, N >::operator=(Map&& rhs) noexcept(noexcept(swap(std::declval< Map >())))
{
  Map temp = std::move(*this);
  swap(rhs);
  return *this;
}
template< class Key, class Value, class Compare, size_t N >
rychkov::Map< Key, Value, Compare, N >::~Map()
{
  clear();
}
template< class Key, class Value, class Compare, size_t N >
void rychkov::Map< Key, Value, Compare, N >::swap(Map& rhs) noexcept(is_nothrow_swappable_v< value_type >)
{
  std::swap(comp_, rhs.comp_);
  std::swap(fake_parent_, rhs.fake_parent_);
  std::swap(fake_children_[0], rhs.fake_children_[0]);
  std::swap(fake_children_[node_capacity], rhs.fake_children_[node_capacity]);
  std::swap(size_, rhs.size_);
}
template< class Key, class Value, class Compare, size_t N >
void rychkov::Map< Key, Value, Compare, N >::clear()
{
  destroy_subtree(fake_root());
}
template< class Key, class Value, class Compare, size_t N >
void rychkov::Map< Key, Value, Compare, N >::destroy_subtree(node_type* node)
{
  if (node == nullptr)
  {
    return;
  }
  for (typename node_type::size_type i = 0; i < node->size(); i++)
  {
    node_type* child = node->getChild(i);
    destroy_subtree(child);
    delete child;
  }
}

#endif

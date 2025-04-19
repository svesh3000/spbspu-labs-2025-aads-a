#ifndef TWO_THREE_TREE_DEFINITION_HPP
#define TWO_THREE_TREE_DEFINITION_HPP

#include "declaration.hpp"

template< class Key, class T, class Compare >
maslevtsov::TwoThreeTree< Key, T, Compare >::TwoThreeTree():
  dummy_root_(new Node{value_type(), value_type(), nullptr, nullptr, nullptr, nullptr, true}),
  size_(0)
{}

template< class Key, class T, class Compare >
maslevtsov::TwoThreeTree< Key, T, Compare >::TwoThreeTree(const TwoThreeTree& rhs):
  TwoThreeTree()
{
  for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(std::make_pair(it.first, it.second));
  }
}

template< class Key, class T, class Compare >
maslevtsov::TwoThreeTree< Key, T, Compare >::TwoThreeTree(TwoThreeTree&& rhs) noexcept:
  dummy_root_(std::exchange(rhs.dummy_root_, nullptr)),
  size_(std::exchange(rhs.size_, 0))
{}

template< class Key, class T, class Compare >
maslevtsov::TwoThreeTree< Key, T, Compare >::~TwoThreeTree()
{
  clear();
  delete dummy_root_;
}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::TwoThreeTree&
  maslevtsov::TwoThreeTree< Key, T, Compare >::operator=(const TwoThreeTree& rhs)
{
  if (dummy_root_ != rhs.dummy_root_) {
    TwoThreeTree< Key, T, Compare > copied_rhs(rhs);
    swap(copied_rhs);
  }
  return *this;
}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::TwoThreeTree&
  maslevtsov::TwoThreeTree< Key, T, Compare >::operator=(TwoThreeTree&& rhs) noexcept
{
  if (dummy_root_ != rhs.dummy_root_) {
    TwoThreeTree< Key, T, Compare > moved_rhs(std::move(rhs));
    swap(moved_rhs);
  }
  return *this;
}

template< class Key, class T, class Compare >
T& maslevtsov::TwoThreeTree< Key, T, Compare >::operator[](const Key& key) noexcept
{}

template< class Key, class T, class Compare >
T& maslevtsov::TwoThreeTree< Key, T, Compare >::operator[](Key&& key) noexcept
{}

template< class Key, class T, class Compare >
T& at(const Key& key)
{}

template< class Key, class T, class Compare >
const T& maslevtsov::TwoThreeTree< Key, T, Compare >::at(const Key& key) const
{}

// template< class Key, class T, class Compare >
// typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator maslevtsov::TwoThreeTree< Key, T, Compare >::begin()
// {}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator
  maslevtsov::TwoThreeTree< Key, T, Compare >::begin() const
{
  return {const_iterator::get_min_node(dummy_root_->left_), true};
}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator
  maslevtsov::TwoThreeTree< Key, T, Compare >::cbegin() const noexcept
{
  return {const_iterator::get_min_node(dummy_root_->left_), true};
}

// template< class Key, class T, class Compare >
// typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator maslevtsov::TwoThreeTree< Key, T, Compare >::end()
// {}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator
  maslevtsov::TwoThreeTree< Key, T, Compare >::end() const
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator
  maslevtsov::TwoThreeTree< Key, T, Compare >::cend() const noexcept
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
bool maslevtsov::TwoThreeTree< Key, T, Compare >::empty() const
{
  return size_ == 0;
}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::size_type
  maslevtsov::TwoThreeTree< Key, T, Compare >::size() noexcept
{
  return size_;
}

template< class Key, class T, class Compare >
void clear() noexcept
{
  clear_subtree(dummy_root_->left_);
  dummy_root_->left_ = nullptr;
}

// template< class Key, class T, class Compare >
// std::pair< typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator, bool >
//   maslevtsov::TwoThreeTree< Key, T, Compare >::insert(const value_type& value)
// {}

// template< class Key, class T, class Compare >
// typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator
//   maslevtsov::TwoThreeTree< Key, T, Compare >::erase(typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator
//   pos)
// {}

// template< class Key, class T, class Compare >
// typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator
//   erase(typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator pos)
// {}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::size_type erase(const Key& key)
{}

template< class Key, class T, class Compare >
void maslevtsov::TwoThreeTree< Key, T, Compare >::swap(TwoThreeTree& other) noexcept
{
  std::swap(dummy_root_, other.dummy_root_);
  std::swap(size_, other.size_);
}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::size_type
  maslevtsov::TwoThreeTree< Key, T, Compare >::count(const Key& key) const
{}

// template< class Key, class T, class Compare >
// typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator
//   maslevtsov::TwoThreeTree< Key, T, Compare >::find(const Key& key)
// {}

template< class Key, class T, class Compare >
typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator
  maslevtsov::TwoThreeTree< Key, T, Compare >::find(const Key& key) const
{}

// template< class Key, class T, class Compare >
// std::pair< typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator,
//   typename maslevtsov::TwoThreeTree< Key, T, Compare >::iterator >
//   maslevtsov::TwoThreeTree< Key, T, Compare >::equal_range(const Key& key)
// {}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator,
  typename maslevtsov::TwoThreeTree< Key, T, Compare >::const_iterator >
  maslevtsov::TwoThreeTree< Key, T, Compare >::equal_range(const Key& key) const
{}

template< class Key, class T, class Compare >
void maslevtsov::TwoThreeTree< Key, T, Compare >::clear_subtree(Node* node) noexcept
{
  if (!node) {
    return;
  }
  clear_subtree(node->left_);
  clear_subtree(node->middle_);
  clear_subtree(node->right_);
  delete node;
}

#endif

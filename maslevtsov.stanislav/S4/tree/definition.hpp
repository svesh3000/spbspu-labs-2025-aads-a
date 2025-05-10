#ifndef TREE_DEFINITION_HPP
#define TREE_DEFINITION_HPP

#include "declaration.hpp"
#include <utility>

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::Tree():
  dummy_root_(new Node{value_type(), value_type(), nullptr, nullptr, nullptr, nullptr, true}),
  size_(0),
  compare_(Compare())
{}

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::Tree(const Tree& rhs):
  Tree()
{
  for (auto it = rhs.cbegin(); it != rhs.cend(); ++it) {
    insert(std::make_pair(it->first, it->second));
  }
}

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::Tree(Tree&& rhs) noexcept:
  dummy_root_(std::exchange(rhs.dummy_root_, nullptr)),
  size_(std::exchange(rhs.size_, 0))
{}

template< class Key, class T, class Compare >
maslevtsov::Tree< Key, T, Compare >::~Tree()
{
  clear();
  delete dummy_root_;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::Tree& maslevtsov::Tree< Key, T, Compare >::operator=(const Tree& rhs)
{
  if (dummy_root_ != rhs.dummy_root_) {
    Tree< Key, T, Compare > copied_rhs(rhs);
    swap(copied_rhs);
  }
  return *this;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::Tree& maslevtsov::Tree< Key, T, Compare >::operator=(Tree&& rhs) noexcept
{
  if (dummy_root_ != rhs.dummy_root_) {
    Tree< Key, T, Compare > moved_rhs(std::move(rhs));
    swap(moved_rhs);
  }
  return *this;
}

template< class Key, class T, class Compare >
T& maslevtsov::Tree< Key, T, Compare >::operator[](const Key& key)
{
  return insert(std::make_pair(key, T())).first->second;
}

template< class Key, class T, class Compare >
T& maslevtsov::Tree< Key, T, Compare >::operator[](Key&& key)
{
  return insert(std::make_pair(std::move(key), T())).first->second;
}

template< class Key, class T, class Compare >
T& maslevtsov::Tree< Key, T, Compare >::at(const Key& key)
{
  iterator it = find(key);
  if (it != end()) {
    return it->second;
  }
  throw std::out_of_range("invalid key");
}

template< class Key, class T, class Compare >
const T& maslevtsov::Tree< Key, T, Compare >::at(const Key& key) const
{
  const_iterator it = find(key);
  if (it != cend()) {
    return it->second;
  }
  throw std::out_of_range("invalid key");
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::iterator maslevtsov::Tree< Key, T, Compare >::begin()
{
  return {iterator::get_min_node(dummy_root_->left), true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator maslevtsov::Tree< Key, T, Compare >::begin() const
{
  return {const_iterator::get_min_node(dummy_root_->left), true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator
  maslevtsov::Tree< Key, T, Compare >::cbegin() const noexcept
{
  return {const_iterator::get_min_node(dummy_root_->left), true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::iterator maslevtsov::Tree< Key, T, Compare >::end()
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator maslevtsov::Tree< Key, T, Compare >::end() const
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator maslevtsov::Tree< Key, T, Compare >::cend() const noexcept
{
  return {dummy_root_, true};
}

template< class Key, class T, class Compare >
bool maslevtsov::Tree< Key, T, Compare >::empty() const noexcept
{
  return size_ == 0;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::size_type maslevtsov::Tree< Key, T, Compare >::size() const noexcept
{
  return size_;
}

template< class Key, class T, class Compare >
void maslevtsov::Tree< Key, T, Compare >::clear() noexcept
{
  Node* current = iterator::get_min_node(dummy_root_);
  while (current && current != dummy_root_) {
    Node* cur_parent = current->parent;
    Node* next = nullptr;
    if (cur_parent->left == current) {
      if (cur_parent->middle) {
        next = cur_parent->middle;
      } else {
        next = cur_parent->right;
      }
      next = iterator::get_min_node(next);
    } else if (cur_parent->middle == current) {
      next = iterator::get_min_node(cur_parent->right);
    } else {
      next = cur_parent;
    }
    delete current;
    current = next;
  }
  size_ = 0;
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::iterator, bool >
  maslevtsov::Tree< Key, T, Compare >::insert(const value_type& value)
{
  if (empty()) {
    Node* new_node = new Node{value, value, dummy_root_, nullptr, nullptr, nullptr, true};
    dummy_root_->left = new_node;
    ++size_;
    return {iterator(new_node, true), true};
  }
  auto result = find_impl(value.first);
  if (result.second) {
    return result;
  }
  Node* current = dummy_root_->left;
  while (current->left || current->middle || (!current->is_two && current->right)) {
    if (current->is_two) {
      if (compare_(value.first, current->data1.first)) {
        current = current->left;
      } else {
        current = current->right;
      }
    } else {
      if (compare_(value.first, current->data1.first)) {
        current = current->left;
      } else if (compare_(value.first, current->data2.first)) {
        current = current->middle;
      } else {
        current = current->right;
      }
    }
  }
  if (current->is_two) {
    if (compare_(value.first, current->data1.first)) {
      current->data1 = value;
      current->is_two = false;
      ++size_;
      return {iterator(current, true), true};
    }
    current->data2 = value;
    current->is_two = false;
    ++size_;
    return {iterator(current, false), true};
  }
  value_type to_insert = value;
  value_type values_to_split[3] = {current->data1, current->data2, to_insert};
  if (compare_(values_to_split[2].first, values_to_split[0].first)) {
    std::swap(values_to_split[2], values_to_split[0]);
  }
  if (compare_(values_to_split[1].first, values_to_split[0].first)) {
    std::swap(values_to_split[1], values_to_split[0]);
  }
  if (compare_(values_to_split[2].first, values_to_split[1].first)) {
    std::swap(values_to_split[2], values_to_split[1]);
  }
  split_nodes(current, values_to_split);
  ++size_;
  return find_impl(value.first);
}

template< class Key, class T, class Compare >
void maslevtsov::Tree< Key, T, Compare >::swap(Tree& other) noexcept
{
  std::swap(dummy_root_, other.dummy_root_);
  std::swap(size_, other.size_);
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::size_type
  maslevtsov::Tree< Key, T, Compare >::count(const Key& key) const noexcept
{
  if (find(key) != cend()) {
    return 1;
  }
  return 0;
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::iterator
  maslevtsov::Tree< Key, T, Compare >::find(const Key& key) noexcept
{
  auto result = find_impl(key);
  if (result.second) {
    return iterator(result.first.node_, result.first.is_first_);
  }
  return end();
}

template< class Key, class T, class Compare >
typename maslevtsov::Tree< Key, T, Compare >::const_iterator
  maslevtsov::Tree< Key, T, Compare >::find(const Key& key) const noexcept
{
  auto result = find_impl(key);
  if (result.second) {
    return const_iterator(result.first.node_, result.first.is_first_);
  }
  return cend();
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::iterator,
  typename maslevtsov::Tree< Key, T, Compare >::iterator >
  maslevtsov::Tree< Key, T, Compare >::equal_range(const Key& key)
{
  iterator first_it = find_impl(key).first;
  iterator second_it = first_it;
  if (second_it != end()) {
    ++second_it;
  }
  return std::make_pair(first_it, second_it);
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::const_iterator,
  typename maslevtsov::Tree< Key, T, Compare >::const_iterator >
  maslevtsov::Tree< Key, T, Compare >::equal_range(const Key& key) const
{
  iterator it = find_impl(key).first;
  const_iterator first_it = const_iterator(it.node_, it.is_first_);
  const_iterator second_it = first_it;
  if (second_it != cend()) {
    ++second_it;
  }
  return std::make_pair(first_it, second_it);
}

template< class Key, class T, class Compare >
void maslevtsov::Tree< Key, T, Compare >::split_nodes(Node* node, value_type (&values)[3])
{
  Node* parent = node->parent;
  value_type left_val = values[0];
  value_type mid_val = values[1];
  value_type right_val = values[2];
  Node* left_node = new Node{left_val, left_val, parent, nullptr, nullptr, nullptr, true};
  Node* right_node = nullptr;
  try {
    right_node = new Node{right_val, right_val, parent, nullptr, nullptr, nullptr, true};
  } catch (const std::bad_alloc&) {
    delete left_node;
    throw;
  }
  if (parent == dummy_root_) {
    Node* new_root = nullptr;
    try {
      new_root = new Node{mid_val, mid_val, dummy_root_, left_node, nullptr, right_node, true};
    } catch (const std::bad_alloc&) {
      delete left_node;
      delete right_node;
      throw;
    }
    left_node->parent = new_root;
    right_node->parent = new_root;
    dummy_root_->left = new_root;
    return;
  }
  if (parent->is_two) {
    if (compare_(mid_val.first, parent->data1.first)) {
      parent->data2 = parent->data1;
      parent->data1 = mid_val;
      parent->right = parent->middle;
      parent->left = left_node;
      parent->middle = right_node;
    } else {
      parent->data2 = mid_val;
      parent->middle = left_node;
      parent->right = right_node;
    }
    parent->is_two = false;
    left_node->parent = parent;
    right_node->parent = parent;
    return;
  }
  if (compare_(mid_val.first, parent->data1.first)) {
    values[2] = parent->data2;
    values[1] = parent->data1;
    values[0] = mid_val;
  } else if (compare_(mid_val.first, parent->data2.first)) {
    values[0] = parent->data1;
    values[1] = mid_val;
    values[2] = parent->data2;
  } else {
    values[0] = parent->data1;
    values[1] = parent->data2;
    values[2] = mid_val;
  }
  split_nodes(parent, values);
}

template< class Key, class T, class Compare >
std::pair< typename maslevtsov::Tree< Key, T, Compare >::iterator, bool >
  maslevtsov::Tree< Key, T, Compare >::find_impl(const Key& key) const noexcept
{
  if (empty()) {
    return {iterator(dummy_root_, true), true};
  }
  Node* current = dummy_root_->left;
  Node* greater = nullptr;
  bool greater_is_first = true;
  while (current) {
    if (!compare_(key, current->data1.first) && !compare_(current->data1.first, key)) {
      return std::make_pair(iterator(current, true), true);
    }
    if (!current->is_two && !compare_(key, current->data2.first) && !compare_(current->data2.first, key)) {
      return std::make_pair(iterator(current, false), true);
    }
    if (compare_(key, current->data1.first)) {
      greater = current;
      greater_is_first = true;
      current = current->left;
    } else if (!current->is_two && compare_(key, current->data2.first)) {
      greater = current;
      greater_is_first = false;
      current = current->middle;
    } else {
      current = current->right;
    }
  }
  if (greater) {
    return std::make_pair(iterator(greater, greater_is_first), false);
  } else {
    return std::make_pair(iterator(dummy_root_, true), false);
  }
}

#endif

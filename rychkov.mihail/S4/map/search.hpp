#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "declaration.hpp"

template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::lower_bound_impl(const K& key) const
{
  if (size_ == 0)
  {
    return end();
  }
  const_iterator left = {fake_children_[0], 0}, right = end();
  while (true)
  {
    for (node_size_type i = 0; i < left.node_->size(); i++)
    {
      if (comp_.comp(key, left.node_->operator[](i).first))
      {
        right = {left.node_, i};
        if (left.node_->isleaf())
        {
          return right;
        }
        left = {left.node_->children[i], 0};
        i = -1;
      }
      else if (!comp_.comp(left.node_->operator[](i).first, key))
      {
        return {left.node_, i};
      }
    }
    if (left.node_->isleaf())
    {
      return right;
    }
    left = {left.node_->children[node_capacity], 0};
  }
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::upper_bound_impl(const K& key) const
{
  if (size_ == 0)
  {
    return end();
  }
  const_iterator left = {fake_children_[0], 0}, right = end();
  while (true)
  {
    node_size_type i = 0;
    while (i < left.node_->size())
    {
      if (comp_.comp(key, left.node_->operator[](i).first))
      {
        right = {left.node_, i};
        if (left.node_->isleaf())
        {
          return right;
        }
        left = {left.node_->children[i], 0};
        i = 0;
        continue;
      }
      i++;
    }
    if (left.node_->isleaf())
    {
      return right;
    }
    left = {left.node_->children[i], 0};
  }
}

template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::lower_bound(const key_type& key)
{
  const_iterator temp = lower_bound_impl(key);
  return {temp.node_, temp.pointed_};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::lower_bound(const key_type& key) const
{
  return lower_bound_impl(key);
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::upper_bound(const key_type& key)
{
  const_iterator temp = upper_bound_impl(key);
  return {temp.node_, temp.pointed_};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::upper_bound(const key_type& key) const
{
  return upper_bound_impl(key);
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::find(const key_type& key)
{
  const_iterator temp = lower_bound(key);
  return ((temp != end()) && !comp_.comp(key, temp->first)) ? iterator{temp.node_, temp.pointed_} : end();
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::find(const key_type& key) const
{
  const_iterator temp = lower_bound(key);
  return ((temp != end()) && !comp_.comp(key, temp->first)) ? temp : end();
}
template< class Key, class Mapped, class Compare, size_t N >
bool rychkov::Map< Key, Mapped, Compare, N >::contains(const key_type& key) const
{
  const_iterator temp = lower_bound(key);
  return (temp != end()) && !comp_.comp(key, temp->first);
}

template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::lower_bound
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key)
{
  const_iterator temp = lower_bound_impl(key);
  return {temp.node_, temp.pointed_};
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::lower_bound
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key) const
{
  return lower_bound_impl(key);
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::upper_bound
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key)
{
  const_iterator temp = upper_bound_impl(key);
  return {temp.node_, temp.pointed_};
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::upper_bound
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key) const
{
  return upper_bound_impl(key);
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::find
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key)
{
  const_iterator temp = lower_bound(key);
  return ((temp != end()) && !comp_.comp(key, temp->first)) ? iterator{temp.node_, temp.pointed_} : end();
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::find
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key) const
{
  const_iterator temp = lower_bound(key);
  return ((temp != end()) && !comp_.comp(key, temp->first)) ? temp : end();
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
bool rychkov::Map< Key, Mapped, Compare, N >::contains
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key) const
{
  const_iterator temp = lower_bound(key);
  return (temp != end()) && !comp_.comp(key, temp->first);
}

#endif

#ifndef ACCESS_HPP
#define ACCESS_HPP

#include "declaration.hpp"
#include <limits>
#include <stdexcept>

template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::node_type*
    rychkov::Map< Key, Mapped, Compare, N >::fake_root() const noexcept
{
  return getFakePointer(fake_parent_, &node_type::parent);
}

template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::mapped_type&
    rychkov::Map< Key, Mapped, Compare, N >::at(const key_type& key)
{
  iterator temp = find(key);
  if (temp == end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class Key, class Mapped, class Compare, size_t N >
const typename rychkov::Map< Key, Mapped, Compare, N >::mapped_type&
    rychkov::Map< Key, Mapped, Compare, N >::at(const key_type& key) const
{
  const_iterator temp = find(key);
  if (temp == end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
typename rychkov::Map< Key, Mapped, Compare, N >::mapped_type&
    rychkov::Map< Key, Mapped, Compare, N >::at
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key)
{
  iterator temp = find(key);
  if (temp == end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class Key, class Mapped, class Compare, size_t N >
template< class K >
const typename rychkov::Map< Key, Mapped, Compare, N >::mapped_type&
    rychkov::Map< Key, Mapped, Compare, N >::at
    (std::enable_if_t< rychkov::is_transparent_v< Compare >, const K& > key) const
{
  const_iterator temp = find(key);
  if (temp == end())
  {
    throw std::out_of_range("at index out of range");
  }
  return temp->second;
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::mapped_type&
    rychkov::Map< Key, Mapped, Compare, N >::operator[](const key_type& key)
{
  iterator temp = find(key);
  if (temp == end())
  {
    return emplace(key, mapped_type{}).first->second;
  }
  return temp->second;
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::mapped_type&
    rychkov::Map< Key, Mapped, Compare, N >::operator[](key_type&& key)
{
  iterator temp = find(key);
  if (temp == end())
  {
    return emplace(std::move(key), mapped_type{}).first->second;
  }
  return temp->second;
}
template< class Key, class Mapped, class Compare, size_t N >
bool rychkov::Map< Key, Mapped, Compare, N >::empty() const noexcept
{
  return size_ == 0;
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::size_type
    rychkov::Map< Key, Mapped, Compare, N >::size() const noexcept
{
  return size_;
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::size_type
    rychkov::Map< Key, Mapped, Compare, N >::maxsize() const noexcept
{
  return std::numeric_limits< difference_type >::max();
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::key_compare
    rychkov::Map< Key, Mapped, Compare, N >::key_comp() const
{
  return comp_.comp;
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::value_compare
    rychkov::Map< Key, Mapped, Compare, N >::value_comp() const
{
  return comp_;
}

template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::begin() noexcept
{
  return {cached_begin_, 0};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::begin() const noexcept
{
  return cbegin();
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::cbegin() const noexcept
{
  return {cached_begin_, 0};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::reverse_iterator
    rychkov::Map< Key, Mapped, Compare, N >::rbegin() noexcept
{
  return {cached_rbegin_, cached_rbegin_->size() - 1};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_reverse_iterator
    rychkov::Map< Key, Mapped, Compare, N >::rbegin() const noexcept
{
  return crbegin();
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_reverse_iterator
    rychkov::Map< Key, Mapped, Compare, N >::crbegin() const noexcept
{
  return {cached_rbegin_, cached_rbegin_->size() - 1};
}

template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::iterator
    rychkov::Map< Key, Mapped, Compare, N >::end() noexcept
{
  return {fake_root(), 0};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::end() const noexcept
{
  return cend();
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_iterator
    rychkov::Map< Key, Mapped, Compare, N >::cend() const noexcept
{
  return {fake_root(), 0};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::reverse_iterator
    rychkov::Map< Key, Mapped, Compare, N >::rend() noexcept
{
  return {fake_root(), 0};
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_reverse_iterator
    rychkov::Map< Key, Mapped, Compare, N >::rend() const noexcept
{
  return crend();
}
template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::const_reverse_iterator
    rychkov::Map< Key, Mapped, Compare, N >::crend() const noexcept
{
  return {fake_root(), 0};
}

#endif

#ifndef ACCESS_HPP
#define ACCESS_HPP

#include "declaration.hpp"
#include <memory>

template< class Key, class Mapped, class Compare, size_t N >
typename rychkov::Map< Key, Mapped, Compare, N >::node_type*
    rychkov::Map< Key, Mapped, Compare, N >::fake_root() const noexcept
{
  return getFakePointer(fake_parent_, &node_type::parent);
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

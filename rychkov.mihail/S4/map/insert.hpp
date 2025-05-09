#ifndef INSERT_HPP
#define INSERT_HPP

#include "declaration.hpp"
#include <utility>
#include <tuple>
#include <type_traits>

template< class Key, class Value, class Compare, size_t N >
template< class... Args >
std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool >
    rychkov::Map< Key, Value, Compare, N >::emplace(Args&&... args)
{
  value_type temp{std::forward< Args >(args)...};
  return try_emplace(std::move(temp.first), std::move(temp.second));
}
template< class Key, class Value, class Compare, size_t N >
template< class... Args >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::emplace_hint(const_iterator hint, Args&&... args)
{
  value_type temp{std::forward< Args >(args)...};
  return try_emplace(std::move(temp.first), std::move(temp.second));
}

template< class Key, class Value, class Compare, size_t N >
template< class... Args >
std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool >
    rychkov::Map< Key, Value, Compare, N >::try_emplace(const key_type& key, Args&&... args)
{
  return try_emplace_impl(lower_bound(key), key, std::forward< Args >(args)...);
}
template< class Key, class Value, class Compare, size_t N >
template< class... Args >
std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool >
    rychkov::Map< Key, Value, Compare, N >::try_emplace(key_type&& key, Args&&... args)
{
  return try_emplace_impl(lower_bound(key), std::move(key), std::forward< Args >(args)...);
}
template< class Key, class Value, class Compare, size_t N >
template< class K, class... Args >
std::enable_if_t< rychkov::is_transparent_v< typename rychkov::Map< Key, Value, Compare, N >::key_compare >,
      std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool > >
    rychkov::Map< Key, Value, Compare, N >::try_emplace(K&& key, Args&&... args)
{
  return try_emplace_impl(lower_bound(key), std::forward< K >(key), std::forward< Args >(args)...);
}
template< class Key, class Value, class Compare, size_t N >
template< class... Args >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::try_emplace(const_iterator hint, const key_type& key, Args&&... args)
{
  return try_emplace_impl(hint, key, std::forward< Args >(args)...);
}
template< class Key, class Value, class Compare, size_t N >
template< class... Args >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::try_emplace(const_iterator hint, key_type&& key, Args&&... args)
{
  return try_emplace_impl(hint, std::move(key), std::forward< Args >(args)...);
}
template< class Key, class Value, class Compare, size_t N >
template< class K, class... Args >
std::enable_if_t< rychkov::is_transparent_v< typename rychkov::Map< Key, Value, Compare, N >::key_compare >,
      typename rychkov::Map< Key, Value, Compare, N >::iterator >
    rychkov::Map< Key, Value, Compare, N >::try_emplace(const_iterator hint, K&& key, Args&&... args)
{
  return try_emplace_impl(hint, std::forward< K >(key), std::forward< Args >(args)...);
}

template< class Key, class Value, class Compare, size_t N >
template< class K, class... Args >
std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool >
    rychkov::Map< Key, Value, Compare, N >::try_emplace_impl(const_iterator hint, K&& key, Args&&... args)
{
  if ((hint != end()) && !comp_.comp(key, hint->first))
  {
    return {{hint.node_, hint.pointed_}, false};
  }
  return {emplace_hint_impl(hint, std::piecewise_construct,
        std::forward_as_tuple(std::forward< K >(key)), std::forward_as_tuple(std::forward< Args >(args)...)), true};
}

template< class Key, class Value, class Compare, size_t N >
std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool >
    rychkov::Map< Key, Value, Compare, N >::insert(const value_type& value)
{
  return try_emplace(value.first, value.second);
}
template< class Key, class Value, class Compare, size_t N >
std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool >
    rychkov::Map< Key, Value, Compare, N >::insert(value_type&& value)
{
  return try_emplace(std::move(value.first), std::move(value.second));
}
template< class Key, class Value, class Compare, size_t N >
template< class T >
std::enable_if_t< std::is_constructible< typename rychkov::Map< Key, Value, Compare, N >::value_type, T&& >::value,
      std::pair< typename rychkov::Map< Key, Value, Compare, N >::iterator, bool > >
    rychkov::Map< Key, Value, Compare, N >::insert(T&& value)
{
  return emplace(std::forward< T >(value));
}
template< class Key, class Value, class Compare, size_t N >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::insert(const_iterator hint, const value_type& value)
{
  return try_emplace_impl(hint, value.first, value.second);
}
template< class Key, class Value, class Compare, size_t N >
typename rychkov::Map< Key, Value, Compare, N >::iterator
    rychkov::Map< Key, Value, Compare, N >::insert(const_iterator hint, value_type&& value)
{
  return try_emplace_impl(hint, std::move(value.first), std::move(value.second));
}
template< class Key, class Value, class Compare, size_t N >
template< class T >
std::enable_if_t< std::is_constructible< typename rychkov::Map< Key, Value, Compare, N >::value_type, T&& >::value,
      typename rychkov::Map< Key, Value, Compare, N >::iterator >
    rychkov::Map< Key, Value, Compare, N >::insert(const_iterator hint, T&& value)
{
  return emplace_hint(hint, std::forward< T >(value));
}
template< class Key, class Value, class Compare, size_t N >
template< class InputIter >
void rychkov::Map< Key, Value, Compare, N >::insert(InputIter from, InputIter to)
{
  for (; from != to; ++from)
  {
    insert(*from);
  }
}
template< class Key, class Value, class Compare, size_t N >
void rychkov::Map< Key, Value, Compare, N >::insert(std::initializer_list< value_type > list)
{
  insert(list.begin(), list.end());
}

#endif

#ifndef MAP_BASE_INSERT_HPP
#define MAP_BASE_INSERT_HPP

#include "declaration.hpp"

#include <utility>
#include <tuple>

template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< class K1 >
std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::const_iterator, bool >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::find_hint_pair(const K1& key) const
{
  const_iterator hint = lower_bound_impl(key).first;
  if (!IsMulti && (hint.pointed_ < hint.node_->size()) && !compare_with_key(key, *hint))
  {
    return {hint, false};
  }
  return {hint, true};
}

template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< class... Args >
std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator, bool >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::emplace(Args&&... args)
{
  real_value_type temp{std::forward< Args >(args)...};
  return emplace_hint_impl(find_hint_pair(get_key(temp)), std::move(temp));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< class... Args >
typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::emplace_hint(const_iterator hint, Args&&... args)
{
  real_value_type temp{std::forward< Args >(args)...};
  return emplace_hint_impl(correct_hint(hint), std::move(temp));
}

template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< bool IsSet2, class... Args >
std::enable_if_t< !IsSet && !IsSet2,
      std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator, bool > >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::try_emplace(const key_type& key, Args&&... args)
{
  return emplace_hint_impl(find_hint_pair(key), std::piecewise_construct,
        std::forward_as_tuple(key), std::forward_as_tuple(std::forward< Args >(args)...));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< bool IsSet2, class... Args >
std::enable_if_t< !IsSet && !IsSet2,
      std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator, bool > >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::try_emplace(key_type&& key, Args&&... args)
{
  return emplace_hint_impl(find_hint_pair(key), std::piecewise_construct,
        std::forward_as_tuple(std::move(key)), std::forward_as_tuple(std::forward< Args >(args)...));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< bool IsSet2, class K1, class... Args >
std::enable_if_t< !IsSet && !IsSet2
      && rychkov::is_transparent_v< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::key_compare >,
      std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator, bool > >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::try_emplace(K1&& key, Args&&... args)
{
  return emplace_hint_impl(find_hint_pair(key), std::piecewise_construct,
        std::forward_as_tuple(std::forward< K1 >(key)), std::forward_as_tuple(std::forward< Args >(args)...));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< bool IsSet2, class... Args >
std::enable_if_t< !IsSet && !IsSet2, typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::try_emplace(const_iterator hint, const key_type& key, Args&&... args)
{
  return emplace_hint_impl(correct_hint(hint), key, std::forward< Args >(args)...).first;
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< bool IsSet2, class... Args >
std::enable_if_t< !IsSet && !IsSet2, typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::try_emplace(const_iterator hint, key_type&& key, Args&&... args)
{
  return emplace_hint_impl(correct_hint(hint), std::move(key), std::forward< Args >(args)...).first;
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< bool IsSet2, class K1, class... Args >
std::enable_if_t< !IsSet && !IsSet2
      && rychkov::is_transparent_v< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::key_compare >,
      typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::try_emplace(const_iterator hint, K1&& key, Args&&... args)
{
  return emplace_hint_impl(correct_hint(hint), std::forward< K1 >(key), std::forward< Args >(args)...).first;
}

template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator, bool >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(const value_type& value)
{
  return emplace_hint_impl(find_hint_pair(get_key(value)), value);
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator, bool >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(value_type&& value)
{
  return emplace_hint_impl(find_hint_pair(get_key(value)), std::move(value));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< class V >
std::enable_if_t< std::is_constructible< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::value_type, V&& >::value,
      std::pair< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator, bool > >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(V&& value)
{
  return emplace(std::forward< V >(value));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(const_iterator hint, const value_type& value)
{
  return emplace_hint_impl(correct_hint(hint, get_key(value)), value);
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(const_iterator hint, value_type&& value)
{
  return emplace_hint_impl(correct_hint(hint, get_key(value)), std::move(value));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< class V >
std::enable_if_t< std::is_constructible< typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::value_type, V&& >::value,
      typename rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::iterator >
    rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(const_iterator hint, V&& value)
{
  return emplace_hint(hint, std::forward< V >(value));
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
template< class InputIter >
void rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(InputIter from, InputIter to)
{
  for (; from != to; ++from)
  {
    insert(*from);
  }
}
template< class K, class T, class C, size_t N, bool IsSet, bool IsMulti >
void rychkov::MapBase< K, T, C, N, IsSet, IsMulti >::insert(std::initializer_list< value_type > list)
{
  insert(list.begin(), list.end());
}

#endif

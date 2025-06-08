#ifndef UNORDERED_BASE_SEARCH_HPP
#define UNORDERED_BASE_SEARCH_HPP

#include "declaration.hpp"

template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
template< class V >
const typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::key_type&
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::get_key(const V& value)
{
  return value.first;
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
const typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::key_type&
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::get_key(const key_type& key)
{
  return key;
}

/*
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::iterator
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::find(const key_type& key)
{
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::const_iterator
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::find(const key_type& key) const
{
}*/
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
bool rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::contains(const key_type& key) const
{
  return find(key) != end();
}
/*
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::size_type
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::count(const key_type& key) const
{
}

template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
template< class K1 >
typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::transparent_hash_key_t
    < typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::iterator, K1 >
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::find(const K1& key)
{
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
template< class K1 >
typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::transparent_hash_key_t
    < typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::const_iterator, K1 >
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::find(const K1& key) const
{
}*/
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
template< class K1 >
typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::transparent_hash_key_t< bool, K1 >
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::contains(const K1& key) const
{
  return find(key) != end();
}
/*
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
template< class K1 >
typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::transparent_hash_key_t
    < typename rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::size_type, K1 >
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::count(const K1& key) const
{
}*/

#endif

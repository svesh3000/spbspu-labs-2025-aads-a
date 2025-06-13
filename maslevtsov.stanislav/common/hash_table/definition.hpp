#ifndef HASH_TABLE_DEFINITION_HPP
#define HASH_TABLE_DEFINITION_HPP

#include <utility>
#include "declaration.hpp"

template< class Key, class T, class Hash, class KeyEqual >
maslevtsov::HashTable< Key, T, Hash, KeyEqual >::HashTable() noexcept:
  slots_(32),
  size_(0)
{}

template< class Key, class T, class Hash, class KeyEqual >
template< class InputIt >
maslevtsov::HashTable< Key, T, Hash, KeyEqual >::HashTable(InputIt first, InputIt last):
  HashTable()
{
  insert(first, last);
}

template< class Key, class T, class Hash, class KeyEqual >
maslevtsov::HashTable< Key, T, Hash, KeyEqual >::HashTable(std::initializer_list< value_type > ilist):
  HashTable(ilist.begin(), ilist.end())
{}

template< class Key, class T, class Hash, class KeyEqual >
T& maslevtsov::HashTable< Key, T, Hash, KeyEqual >::operator[](const Key& key)
{
  return insert(std::make_pair(key, T())).first->second;
}

template< class Key, class T, class Hash, class KeyEqual >
T& maslevtsov::HashTable< Key, T, Hash, KeyEqual >::at(const Key& key)
{
  iterator it = find(key);
  if (it != end()) {
    return it->second;
  }
  throw std::out_of_range("invalid key");
}

template< class Key, class T, class Hash, class KeyEqual >
const T& maslevtsov::HashTable< Key, T, Hash, KeyEqual >::at(const Key& key) const
{
  const_iterator it = find(key);
  if (it != cend()) {
    return it->second;
  }
  throw std::out_of_range("invalid key");
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::find(const Key& key)
{
  size_t hash_value1 = hasher_(key);
  size_t hash_value2 = hasher_(key);
  for (size_t i = 0; i != slots_.size(); ++i) {
    size_t index = (hash_value1 + i * hash_value2) % slots_.size();
    if (slots_[index].state == SlotState::EMPTY)
      return end();
    if (slots_[index].state == SlotState::OCCUPIED && key_equal_(slots_[index].first, key))
      return iterator(this, index);
  }
  return end();
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::const_iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::find(const Key& key) const
{
  iterator it = find(key);
  return const_iterator(it.table_, it.index_);
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::begin() noexcept
{
  return iterator(this, 0);
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::const_iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::begin() const noexcept
{
  return const_iterator(this, 0);
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::const_iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::cbegin() const noexcept
{
  return const_iterator(this, 0);
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::end() noexcept
{
  return iterator(this, slots_.size());
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::const_iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::end() const noexcept
{
  return const_iterator(this, slots_.size());
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::const_iterator
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::cend() const noexcept
{
  return const_iterator(this, slots_.size());
}

template< class Key, class T, class Hash, class KeyEqual >
bool maslevtsov::HashTable< Key, T, Hash, KeyEqual >::empty() const noexcept
{
  return size_ == 0;
}

template< class Key, class T, class Hash, class KeyEqual >
typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::size_type
  maslevtsov::HashTable< Key, T, Hash, KeyEqual >::size() const noexcept
{
  return size_;
}

// template< class Key, class T, class Hash, class KeyEqual >
// void maslevtsov::HashTable< Key, T, Hash, KeyEqual >::clear() noexcept
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// std::pair< typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator, bool >
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::insert(const value_type& value)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::insert(const_iterator hint, const value_type& value)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// template< class InputIt >
// void maslevtsov::HashTable< Key, T, Hash, KeyEqual >::insert(InputIt first, InputIt last)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// template< class... Args >
// std::pair< typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator, bool >
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::emplace(Args&&... args)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// template< class... Args >
// typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::emplace_hint(const_iterator hint, Args&&... args)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::erase(iterator pos)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::erase(const_iterator pos)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::iterator
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::erase(const_iterator first, const_iterator last)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// typename maslevtsov::HashTable< Key, T, Hash, KeyEqual >::size_type
//   maslevtsov::HashTable< Key, T, Hash, KeyEqual >::erase(const Key& key)
// {}

template< class Key, class T, class Hash, class KeyEqual >
void maslevtsov::HashTable< Key, T, Hash, KeyEqual >::swap(HashTable& other)
{
  std::swap(slots_, other.slots_);
  std::swap(size_, other.size_);
  std::swap(hasher_, other.hasher_);
  std::swap(key_equal_, other.key_equal_);
}

template< class Key, class T, class Hash, class KeyEqual >
float maslevtsov::HashTable< Key, T, Hash, KeyEqual >::load_factor() const
{
  return static_cast< float >(size_) / slots_.size();
}

template< class Key, class T, class Hash, class KeyEqual >
float maslevtsov::HashTable< Key, T, Hash, KeyEqual >::max_load_factor() const
{
  return max_load_factor;
}

// template< class Key, class T, class Hash, class KeyEqual >
// void maslevtsov::HashTable< Key, T, Hash, KeyEqual >::max_load_factor(float ml)
// {}

// template< class Key, class T, class Hash, class KeyEqual >
// void maslevtsov::HashTable< Key, T, Hash, KeyEqual >::rehash(size_type count)
// {}

#endif

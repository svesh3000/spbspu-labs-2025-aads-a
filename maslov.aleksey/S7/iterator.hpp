#ifndef HASH_TABLE_ITERATOR_HPP
#define HASH_TABLE_ITERATOR_HPP

#include <cassert>
#include <iterator>
#include "hashNode.hpp"

namespace maslov
{
  template< class Key, class T, class HS1, class HS2, class EQ >
  struct HashTable;

  template< class Key, class T, class HS1, class HS2, class EQ >
  struct HashIterator
  {
    friend struct HashTable< Key, T, HS1, HS2, EQ >;
    using node = HashNode< Key, Node >;
    HashIterator();
   private:
    explicit HashIterator(node * slots, size_t cap, size_t curr);
    node * slots_;
    size_t capacity_;
    size_t current_;
  };

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashIterator< Key, T, HS1, HS2, EQ >::HashIterator():
    slots_(nullptr),
    capacity_(0),
    current_(0)
  {}

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashIterator< Key, T, HS1, HS2, EQ >::HashIterator(node * slots, size_t cap, size_t curr):
    slots_(slots),
    capacity_(cap),
    current_(curr)
  {}

  template< class Key, class T, class HS1, class HS2, class EQ >
  struct HashCIterator
  {
    friend struct HashTable< Key, T, HS1, HS2, EQ >;
    using node = HashNode< Key, Node >;
    HashCIterator();
   private:
    explicit HashCIterator(node * slots, size_t cap, size_t curr);
    node * slots_;
    size_t capacity_;
    size_t current_;
  };

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashCIterator< Key, T, HS1, HS2, EQ >::HashCIterator():
    slots_(nullptr),
    capacity_(0),
    current_(0)
  {}

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashCIterator< Key, T, HS1, HS2, EQ >::HashCIterator(node * slots, size_t cap, size_t curr):
    slots_(slots),
    capacity_(cap),
    current_(curr)
  {}
}

#endif

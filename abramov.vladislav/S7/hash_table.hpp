#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <cstddef>
#include <functional>
#include "node.hpp"

namespace abramov
{
  template< class Key, class Value, class Hash = std::hash< Key >, class Equal = std::equal_to< Key > >
  struct HashTable
  {
    HashTable();

  private:
    Node< Key, Value > **table_;
    size_t capacity_;
    size_t size_;
    Hash hash_;
    Equal equal_;

    void initTable();
  };
}

template< class Key, class Value, class Hash, class Equal >
abramov::HashTable< Key, Value, Hash, Equal >::HashTable():
  table_(nullptr),
  capacity_(0),
  size_(0),
  hash_(std::hash< Key >()),
  equal_(std::equal_to< Key >())
{
  initTable();
}

template< class Key, class Value, class Hash, class Equal >
void abramov::HashTable< Key, Value, Hash, Equal >::initTable()
{
  constexpr size_t k = 20;
  capacity_ = k;
  table_ = new Node< Key, Value >*[capacity_];
  for (size_t i = 0; i < capacity_; ++i)
  {
    table_[i] = nullptr;
  }
}
#endif

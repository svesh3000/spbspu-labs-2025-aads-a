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
    void insert(const Key &k, const Value &v);
    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    Node< Key, Value > **table_;
    size_t capacity_;
    size_t size_;
    Hash hash_;
    Equal equal_;

    void initTable();
    void resizeIfNeed();
    double loadFactor() const noexcept;
    void rehash(size_t k);
  };
}

template< class Key, class Value, class Hash, class Equal >
abramov::HashTable< Key, Value, Hash, Equal >::HashTable():
  table_(nullptr),
  capacity_(20),
  size_(0),
  hash_(std::hash< Key >()),
  equal_(std::equal_to< Key >())
{
  initTable();
}

template< class Key, class Value, class Hash, class Equal >
void abramov::HashTable< Key, Value, Hash, Equal >::initTable()
{
  table_ = new Node< Key, Value >*[capacity_];
  for (size_t i = 0; i < capacity_; ++i)
  {
    table_[i] = nullptr;
  }
}

template< class Key, class Value, class Hash, class Equal >
void abramov::HashTable< Key, Value, Hash, Equal >::insert(const Key &k, const Value &v)
{
  resizeIfNeed();
  size_t pos = findInsertPosition(k);
  if (!table_[pos])
  {
    table_[pos] = new Node< Key, Value >(k, v);
  }
  else
  {
    Node< Key, Value > *new_node = new Node< Key, Value >(k, v);
    new_node->next_ = table_[pos];
    table_[pos] = new_node;
  }
  ++size_;
}

template< class Key, class Value, class Hash, class Equal >
void abramov::HashTable< Key, Value, Hash, Equal >::resizeIfNeed()
{
  constexpr double max = 0.8;
  if (loadFactor() > max)
  {
    rehash(capacity_ * 2);
  }
}

  template< class Key, class Value, class Hash, class Equal >
  double abramov::HashTable< Key, Value, Hash, Equal >::loadFactor() const noexcept
  {
    return static_cast< double >(size_) / capacity_;
  }

template< class Key, class Value, class Hash, class Equal >
void abramov::HashTable< Key, Value, Hash, Equal >::rehash(size_t k)
{
  Node< Key, Value > **old_table = table_;
  size_t old_capacity = capacity_;
  capacity_ = k;
  size_ = 0;
  initTable();
  for (size_t i = 0; i < old_capacity; ++i)
  {
    Node< Key, Value > *curr = old_table[i];
    while (curr)
    {
      insert(curr->data_.first, curr->data_.second);
      Node< Key, Value > *next = curr->next_;
      delete curr;
      curr = next;
    }
  }
  delete[] old_table;
}

template< class Key, class Value, class Hash, class Equal >
size_t abramov::HashTable< Key, Value, Hash, Equal >::size() const noexcept
{
  return size_;
}

template< class Key, class Value, class Hash, class Equal >
bool abramov::HashTable< Key, Value, Hash, Equal >::empty() const noexcept
{
  return size_ == 0;
}
#endif

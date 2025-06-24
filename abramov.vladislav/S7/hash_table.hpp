#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <cmath>
#include <cstddef>
#include <functional>
#include "node.hpp"
#include "cIterator.hpp"

namespace abramov
{
  template< class Key, class Value, class Hash = std::hash< Key >, class Equal = std::equal_to< Key > >
  struct HashTable
  {
    HashTable();
    void insert(const Key &k, const Value &v);
    double loadFactor() const noexcept;
    void rehash(size_t k);
    size_t erase(const Key &k);
    ConstIterator< Key, Value, Hash, Equal > cbegin() const noexcept;
    ConstIterator< Key, Value, Hash, Equal > cend() const noexcept;
    ConstIterator< Key, Value, Hash, Equal > cfind(const Key &k) const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    Node< Key, Value > **table_;
    size_t capacity_;
    size_t size_;
    Hash hash_;
    Equal equal_;
    friend struct ConstIterator< Key, Value, Hash, Equal >;

    void initTable();
    void resizeIfNeed();
    size_t findInsertPosition(const Key &k) const;
    bool isPrime(size_t k) const noexcept;
    size_t getLargerPrimeCapacity(size_t k) const noexcept;
  };
}

template< class Key, class Value, class Hash, class Equal >
abramov::HashTable< Key, Value, Hash, Equal >::HashTable():
  table_(nullptr),
  capacity_(17),
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
size_t abramov::HashTable< Key, Value, Hash, Equal >::findInsertPosition(const Key &k) const
{
  size_t pos = hash_(k) % capacity_;
  size_t att = 0;
  while (table_[pos] && !equal_(table_[pos]->data_.first, k))
  {
    pos = (pos + att * att) % capacity_;
    ++att;
  }
  return pos;
}

template< class Key, class Value, class Hash, class Equal >
size_t abramov::HashTable< Key, Value, Hash, Equal >::erase(const Key &k)
{
  size_t removed = 0;
  size_t orig_pos = hash_(k) % capacity_;
  size_t pos = orig_pos;
  size_t att = 0;
  do
  {
    Node< Key, Value > *curr = table_[pos];
    Node< Key, Value > *prev = nullptr;
    while (curr)
    {
      if (equal_(curr->data_.first, k))
      {
        Node< Key, Value > *del = curr;
        if (prev)
        {
          prev->next_ = curr->next_;
        }
        else
        {
          table_[pos] = curr->next_;
        }
      }
      else
      {
        prev = curr;
        curr = curr->next_;
      }
    }
    ++att;
    pos = (orig_pos + att * att) & capacity_;
  } while (pos != orig_pos);
  return removed;
}

template< class Key, class Value, class Hash, class Equal >
abramov::ConstIterator< Key, Value, Hash, Equal > abramov::HashTable< Key, Value, Hash, Equal >::cend() const noexcept
{
  return ConstIterator< Key, Value, Hash, Equal >(this, capacity_, nullptr);
}

template< class Key, class Value, class Hash, class Equal >
abramov::ConstIterator< Key, Value, Hash, Equal > abramov::HashTable< Key, Value, Hash, Equal >::cbegin() const noexcept
{
  for (size_t i = 0; i < capacity_; ++i)
  {
    if (table_[i])
    {
      return ConstIterator< Key, Value, Hash, Equal >(this, i, table_[i]);
    }
  }
  return cend();
}

template< class Key, class Value, class Hash, class Equal >
abramov::ConstIterator< Key, Value, Hash, Equal > abramov::HashTable< Key, Value, Hash, Equal >::cfind(const Key & k) const noexcept
{
  if (empty())
  {
    return cend();
  }
  size_t pos = hash_(k) % capacity_;
  size_t att = 0;
  size_t orig_pos = pos;
  do
  {
    Node< Key, Value > *curr = table_[pos];
    while (curr)
    {
      if (equal_(curr->data_.first, k))
      {
        return ConstIterator< Key, Value, Hash, Equal >(this, pos, curr);
      }
      curr = curr->next_;
    }
    ++att;
    pos = (orig_pos + att * att) % capacity_;
  } while (pos != orig_pos);
  return cend();
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

template< class Key, class Value, class Hash, class Equal >
bool abramov::HashTable< Key, Value, Hash, Equal >::isPrime(size_t k) const noexcept
{
  if (k % 2 == 0)
  {
    return true;
  }
  for (size_t i = 3; i < static_cast< int >(std::ceil(std::sqrt(k))); ++i)
  {
    if (k % i == 0)
    {
      return false;
    }
  }
  return true;
}

template< class Key, class Value, class Hash, class Equal >
size_t abramov::HashTable< Key, Value, Hash, Equal >::getLargerPrimeCapacity(size_t k) const noexcept
{
  size_t cand = 2 * cand + 1;
  while (true)
  {
    if (isPrime(cand))
    {
      return cand;
    }
    ++cand;
  }
}
#endif


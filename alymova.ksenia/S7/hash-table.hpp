#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <functional>
#include "hash-node.hpp"
#include "hash-iterators.hpp"

namespace alymova
{
  template< class Key, class Value, class Hash = std::hash< Key >, class KeyEqual = std::equal_to< Key > >
  class HashTable
  {
    using Hashtable = HashTable< Key, Value, Hash, KeyEqual >;
    using Iterator = HashIterator< Key, Value, Hash, KeyEqual >;
    using ConstIterator = HashConstIterator< Key, Value, Hash, KeyEqual >;
    using Node = detail::HashNode< Key, Value >;
    using T = std::pair< Key, Value >;

    HashTable();
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    template< class InputIterator >
    HashTable(InputIterator first, InputIterator last);
    HashTable(std::initializer_list< T > il);
    ~HashTable() noexcept;

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

    Iterator begin() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end() noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    Iterator insert(const T& value);
    Iterator insert(T&& value);

    size_t erase(const Key& key);
    Iterator erase(Iterator pos);
    Iterator erase(ConstIterator pos);

    float load_factor() const noexcept;
    float max_load_factor() const noexcept;
    void max_load_factor(float mlf) noexcept; //resixe if new mlf

    void clear() noexcept;
    void swap(HashTable& other);
  private:
    float max_load_factor_ = 0.7;
    size_t size_;
    size_t size_buffer_;
    Node* array_;
    Hash hasher;

    std::pair< Node, bool > probing(const T& value, size_t home_slot);
  };

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable():
    size_(0),
    size_buffer_(11),
    array_(new Node[size_buffer_]()),
    hasher()
  {
    clear();
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::~HashTable() noexcept
  {
    delete[] array_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >& HashTable< Key, Value, Hash, KeyEqual >::operator=(const HashTable& other)
  {
    HashTable copy(other);
    swap(copy);
    return *this;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >& HashTable< Key, Value, Hash, KeyEqual >::operator=(HashTable&& other) noexcept
  {
    HashTable movy(std::move(other));
    swap(movy);
    return *this;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::begin() noexcept
  {
    return Iterator(array_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::begin() const noexcept
  {
    return cbegin();
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::cbegin() const noexcept
  {
    return ConstIterator(array_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::end() noexcept
  {
    return Iterator(array_ + size_buffer_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::end() const noexcept
  {
    return cend();
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::cend() const noexcept
  {
    return ConstIterator(array_ + size_buffer_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  bool HashTable< Key, Value, Hash, KeyEqual >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  size_t HashTable< Key, Value, Hash, KeyEqual >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::insert(const T& value)
  {
    size_t home_index = hasher(value.first) % size_;
    if (array_[home_index].isEmpty)
    {
      array_[home_index].data = value;
      array_[home_index].psl = 0;
      array_[home_index].isEmpty = false;
      return Iterator(array_[home_index]);
    }
    std::pair< Node, bool > prob_res = probing(value, home_index);
    if (!prob_res.second)
    {}
    if (!prob_res.second.isEmpty)
    {
      return insert(prob_res.first.data);
    }
    return Iterator(prob_res.first);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  float HashTable< Key, Value, Hash, KeyEqual >::load_factor() const noexcept
  {
    return (size_ * 1.0) / (size_buffer_ * 1.0);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  float HashTable< Key, Value, Hash, KeyEqual >::max_load_factor() const noexcept
  {
    return max_load_factor_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::max_load_factor(float mlf) noexcept
  {
    max_load_factor_ = mlf;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::clear() noexcept
  {
    for (size_t i = 0; i < size_buffer_; i++)
    {
      array_[i].isEmpty = false;
      array_[i].psl = 0;
    }
    size_ = 0;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::swap(HashTable& other)
  {
    std::swap(size_, other.size_);
    std::swap(size_buffer_, other.size_buffer_);
    std::swap(hasher, other.hasher);
    std::swap(array_, other.array_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  std::pair< detail::HashNode< Key, Value >, bool >
    HashTable< Key, Value, Hash, KeyEqual >::probing(const T& value, size_t home_slot)
  {
    Node node{value, 1, false};
    for (size_t i = (home_slot + 1) % size_buffer_; i != home_slot; i = (i + 1) % size_buffer_)
    {
      if (node.psl > array_[i].psl)
      {
        node.swap(array_[i]);
        return {node, true};
      }
      node.psl++;
    }
    return {node, false};
  }
}

#endif

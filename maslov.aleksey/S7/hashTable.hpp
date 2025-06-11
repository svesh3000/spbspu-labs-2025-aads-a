#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <functional>
#include <boost/hash2/xxhash.hpp>
#include "iterator.hpp"
#include "hashNode.hpp"

namespace maslov
{
  template< class Key, class T, class HS1 = std::hash< Key >, class HS2 = boost::hash2::xxhash_64, class EQ = std::equal_to< Key > >
  struct HashTable
  {
    HashTable(size_t capacity);
    ~HashTable();
    bool empty() const noexcept;
    size_t size() const noexcept;
    float loadFactor() const;
    void rehash(size_t newCapacity);
    /*T & at(const Key & key);
    const T & at(const Key & key) const;
    T & operator[](const Key & key);
    T & operator[](Key && key);
    void clear() noexcept;
    std::pair< iterator, bool > insert(const T & value);
    template< class InputIt >
    void insert(InputIt first, InputIt last);
    */
   private:
    HashNode< Key, T > * slots_;
    size_t capacity_;
    size_t size_;
    float maxLoadFactor_;
    size_t computexxhash(const Key & key) const;
  };

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashTable< Key, T, HS1, HS2, EQ >::HashTable(size_t capacity):
    slots_(new Entry[capacity]),
    capacity_(capacity),
    size_(0),
    maxLoadFactor_(0.7)
  {}

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashTable< Key, T, HS1, HS2, EQ >::~HashTable()
  {
    delete[] slots_;
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  bool HashTable< Key, T, HS1, HS2, EQ >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  size_t HashTable< Key, T, HS1, HS2, EQ >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  float HashTable< Key, T, HS1, HS2, EQ >::loadFactor() const
  {
    return static_cast< float >(size_) / capacity_;
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  void HashTable< Key, T, HS1, HS2, EQ >::rehash(size_t newCapacity)
  {
    if (newCapacity <= capacity_)
    {
      return;
    }
    HashNode< Key, T > * tmp = new Entry[newCapacity];
    for (size_t i = 0; i < capacity_; ++i)
    {
      if (slots_[i].occupied && !slots_[i].deleted)
      {
        const Key & key = slots_[i].key;
        const T & value = slots_[i].value;
        size_t h1 = HS1{}(key) % newCapacity;
        size_t h2 = computexxhash(key) % (newCapacity - 1) + 1;
        for (size_t j = 0; j < newCapacity; ++j)
        {
          size_t index = (h1 + j * h2) % newCapacity;
          if (!tmp[index].occupied)
          {
            tmp[index].key = key;
            tmp[index].value = value;
            tmp[index].occupied = true;
            break;
          }
        }
      }
    }
    delete[] slots_;
    slots_ = std::move(tmp);
    capacity_ = newCapacity;
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  size_t HashTable< Key, T, HS1, HS2, EQ >::computexxhash(const Key & key) const
  {
    HS2 hasher;
    hasher.update(std::addressof(key), sizeof(Key));
    return hasher.result();
  }
}

#endif

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
    using cIterator = HashConstIterator< Key, T, HS1, HS2, EQ >;
    using iterator = HashIterator< Key, T, HS1, HS2, EQ >;

    HashTable();
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
    void clear() noexcept;*/
    std::pair< iterator, bool > insert(const Key & key, const T & value);
    //template< class InputIt >
    //void insert(InputIt first, InputIt last);

    iterator begin();
    cIterator cbegin() const;
    iterator end();
    cIterator cend() const;
   private:
    HashNode< Key, T > * slots_;
    size_t capacity_;
    size_t size_;
    float maxLoadFactor_;
    size_t computexxhash(const Key & key) const;
    std::pair< size_t, size_t > calculatePositions(const Key & key) const;
    std::pair< size_t, bool > findPosition(const Key & key);
  };

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashTable< Key, T, HS1, HS2, EQ >::HashTable():
    HashTable(10)
  {}

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashTable< Key, T, HS1, HS2, EQ >::HashTable(size_t capacity):
    slots_(new HashNode< Key, T >[capacity]),
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
    HashNode< Key, T > * tmp = nullptr;
    try
    {
      tmp = new HashNode< Key, T >[newCapacity];
      for (size_t i = 0; i < capacity_; ++i)
      {
        if (slots_[i].occupied && !slots_[i].deleted)
        {
          auto pos = findPosition(slots_[i].data.first);
          tmp[pos.first] = slots_[i];
        }
      }
    }
    catch (const std::exception &)
    {
      delete[] tmp;
      throw;
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

  template< class Key, class T, class HS1, class HS2, class EQ >
  std::pair< HashIterator< Key, T, HS1, HS2, EQ >, bool > HashTable< Key, T, HS1, HS2, EQ >::insert(const Key & key, const T & value)
  {
    if (loadFactor() >= maxLoadFactor_)
    {
      rehash(capacity_ * 2);
    }
    auto pair = findPosition(key);
    size_t pos = pair.first;
    bool hasFind   = pair.second; 
    if (pos == capacity_)
    {
      throw std::runtime_error("ERROR: hash table is full");
    }
    if (hasFind)
    {
      slots_[pos].data.first = key;
      slots_[pos].data.second = value;
      slots_[pos].occupied = true;
      slots_[pos].deleted = false;
      size_++;
      return {iterator(slots_, capacity_, pos), true};
    }
    return {iterator(slots_, capacity_, pos), false};
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  std::pair< size_t, size_t > HashTable< Key, T, HS1, HS2, EQ >::calculatePositions(const Key & key) const
  {
    size_t h1 = HS1{}(key) % capacity_;
    size_t h2 = computexxhash(key) % (capacity_ - 1) + 1;
    return {h1, h2};
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  std::pair< size_t, bool > HashTable< Key, T, HS1, HS2, EQ >::findPosition(const Key & key)
  {
    auto pos = calculatePositions(key);
    size_t deleted = capacity_;
    for (size_t i = 0; i < capacity_; ++i)
    {
      size_t index = (pos.first + i * pos.second) % capacity_;
      if (!slots_[index].occupied)
      {
        if (deleted != capacity_)
        {
          return {deleted, true};
        }
        else
        {
          return {index, true};
        }
      }
      else if (slots_[index].deleted && deleted == capacity_)
      {
        deleted = index;
      }
      else if (EQ{}(slots_[index].data.first, key))
      {
        return {index, false};
      }
    }
    return {capacity_, false};
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashIterator< Key, T, HS1, HS2, EQ > HashTable< Key, T, HS1, HS2, EQ >::begin()
  {
    return iterator(slots_, capacity_, 0);
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashIterator< Key, T, HS1, HS2, EQ > HashTable< Key, T, HS1, HS2, EQ >::end()
  {
    return iterator(slots_, capacity_, capacity_);
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashConstIterator< Key, T, HS1, HS2, EQ > HashTable< Key, T, HS1, HS2, EQ >::cbegin() const
  {
    return cIterator(slots_, capacity_, 0);
  }

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashConstIterator< Key, T, HS1, HS2, EQ > HashTable< Key, T, HS1, HS2, EQ >::cend() const
  {
    return cIterator(slots_, capacity_, capacity_);
  }
}

#endif

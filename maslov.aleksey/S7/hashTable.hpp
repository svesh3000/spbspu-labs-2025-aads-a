#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <functional>
#include <boost/hash2/xxhash.hpp>

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
    /*T & at( const Key & key );
    const T & at( const Key & key ) const;
    T & operator[]( const Key & key );
    T & operator[]( Key && key );
    void clear() noexcept;
    std::pair< iterator, bool > insert(const T & value);
    template< class InputIt >
    void insert(InputIt first, InputIt last);
    */
    size_t computexxhash(const Key & key) const
    {
      HS2 hasher;
      hasher.update(std::addressof(key), sizeof(Key));
      return hasher.result();
    }
   private:
    struct Entry
    {
      Key key;
      T value;
      bool occupied;
      bool deleted;
    };
    Entry * slots_;
    size_t capacity_;
    size_t size_;
    float maxLoadFactor_;
  };

  template< class Key, class T, class HS1, class HS2, class EQ >
  HashTable< Key, T, HS1, HS2, EQ >::HashTable(size_t capacity = 1):
    slots_(new Entry[capacity]),
    capacity_(capacity),
    maxLoadFactor_(1.0)
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
}

#endif

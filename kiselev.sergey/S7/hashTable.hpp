#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <utility>
#include <boost/container_hash/hash.hpp>
#include "iteratorHash.hpp"

namespace kiselev
{
  enum class Status
  {
    EMPTY,
    DELETED,
    OCCUPIED
  };

  template< class Key, class Value, class Hash1 = std::hash< Key >, class Hash2 = boost::hash< Value >, class Equal = std::equal_to< Key > >
  class HashTable
  {
  public:
    using value = std::pair< Key, Value >;
    using Iterator = IteratorHash< Key, Value, Hash1, Hash2, Equal, false >;
    using ConstIterator = IteratorHash< Key, Value, Hash1, Hash2, Equal, true >;

    HashTable():
      slots_(10),
      count_(0)
    {}

    HashTable(const HashTable< Key, Value, Hash1, Hash2, Equal >& table):
      HashTable()
    {
      for (ConstIterator it = table.cbegin(); it != table.cend(); ++it)
      {
        insert(*it);
      }
    }

    HashTable(HashTable< Key, Value, Hash1, Hash2, Equal >&& table):
      slots_(std::exchange(table.slots_, table.slots_.clear())),
      count_(std::exchange(table.count_, 0))
    {}

    template< typename InputIt >
    HashTable(InputIt first, InputIt last):
      HashTable()
    {
      for (; first != last; first++)
      {
        insert(*first);
      }
    }

    HashTable(std::initializer_list< value > il):
      HashTable(il.begin(), il.end())
    {}

    ~HashTable()
    {
      clear();
    }

    HashTable& operator=(const HashTable< Key, Value, Hash1, Hash2, Equal >& table)
    {
      HashTable< Key, Value, Hash1, Hash2, Equal > cpy(table);
      swap(cpy);
      return *this;
    }

    HashTable& operator=(HashTable< Key, Value, Hash1, Hash2, Equal >&& table)
    {
      HashTable< Key, Value, Hash1, Hash2, Equal > temp(table);
      swap(temp);
      return *this;
    }

    HashTable& operator=(std::initializer_list< value > il)
    {
      HashTable< Key, Value, Hash1, Hash2, Equal > temp(il);
      swap(temp);
      return *this;
    }

    Value& operator[](const Key&) const;
    Value& operator[](Key&&) const;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

    Iterator erase(Iterator pos);
    Iterator erase(ConstIterator pos);

    template< typename... Args >
    std::pair< Iterator, bool > emplace(Args&&... args);
    template< typename... Args >
    std::pair< Iterator, bool > emplaceHint(ConstIterator hint, Args... args);

    std::pair< Iterator, bool > insert(const value&);
    std::pair< Iterator, bool > insert(value&&);

    Iterator find(const Key& key);
    Iterator find(const Key& key) const;
    void clear() noexcept;
    void swap(HashTable< Key, Value, Hash1, Hash2, Equal >&) noexcept;

    float loadFactor() const;
    void rehash(size_t count);

  private:
    struct Slot
    {
      std::pair< Key, Value > pair;
      Status status = Status::EMPTY;
    };

    std::vector< Slot > slots_;
    size_t count_;
    float MaxloadFactor_ = 0.6;
    Hash1 hash1;
    Hash2 hash2;
    Equal equal;




  };
}
#endif

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
      slots_(std::move(table.slots_)),
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

    Value& operator[](const Key& key);
    Value& operator[](Key&&);

    Iterator begin() noexcept
    {
      size_t index = 0;
      while (index < slots_.size() && slots_[index].status != Status::OCCUPIED)
      {
        ++index;
      }
      return Iterator(this, index);
    }

    Iterator end() noexcept
    {
      return Iterator(this, slots_.size());
    }

    ConstIterator cbegin() const noexcept
    {
      size_t index = 0;
      while (index < slots_.size() && slots_[index].status != Status::OCCUPIED)
      {
        ++index;
      }
      return ConstIterator(this, index);
    }

    ConstIterator cend() const noexcept
    {
      return ConstIterator(this, slots_.size());
    }

    size_t size() const noexcept
    {
      return count_;
    }
    bool empty() const noexcept
    {
      return count_ == 0;
    }

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
    void swap(HashTable< Key, Value, Hash1, Hash2, Equal >& table) noexcept
    {
      std::swap(slots_, table.slots_);
      std::swap(count_, table.count_);
    }

    float loadFactor() const
    {
      return count_ / slots_.size();
    }
    void rehash(size_t count);

  private:
    enum class Status
    {
      EMPTY,
      DELETED,
      OCCUPIED
    };

    struct Slot
    {
      std::pair< Key, Value > pair;
      Status status = Status::EMPTY;
    };

    std::vector< Slot > slots_;
    size_t count_;
    float maxLoadFactor_ = 0.6;
    Hash1 hash1;
    Hash2 hash2;
    Equal equal;
  };
}
#endif

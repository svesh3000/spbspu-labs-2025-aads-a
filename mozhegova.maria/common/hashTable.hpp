#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <functional>
#include "hashSlot.hpp"
#include "hashConstIter.hpp"
#include "hashIter.hpp"
#include "dynamicArray.hpp"

namespace mozhegova
{
  template< class Key, class Value, class Hash = std::hash< Key >, class Equal = std::equal_to< Key > >
  class HashTable
  {
  public:
    using Iter = HashTIterator< Key, T, Hash, Equal >;
    using cIter = HashTIterator< Key, T, Hash, Equal >;

    HashTable();
    template< class InputIt >
    HashTable(InputIt begin, InputIt end);
    HashTable(std::initializer_list< std::pair< Key, Value > > il);

    Value & operator[](const Key & key);
    const Value & operator[](const Key & key) const;
    Value & at(const Key & key);
    const Value & at(const Key & key) const;

    Iter begin();
    cIter cbegin() const;
    Iter end();
    cIter cend() const;

    size_t size() const noexcept;
    bool empty() const noexcept;

    size_t erase(const Key &) noexcept;
    Iter erase(cIter) noexcept;
    Iter erase(CIter first, CIter last) noexcept;

    std::pair< Iter, bool > insert(const std::pair< Key, Value > & val);
    Iter insert(CIter, const std::pair< Key, Value > & val);
    template < class InputIt >
    void insert(InputIt first, InputIt last);

    void clear();
    void swap(HashTable< Key, Value, Hash, Equal > & rhs) noexcept;

    template< class... Args >
    std::pair< Iter, bool > emplace(Args &&... args);

    template< class... Args >
    Iter emplace_hint(cIter hint, Args &&... args);

    Iter find(const Key & k);
    cIter find(const Key & k) const;

    float load_factor() const noexcept;
    float max_load_factor() const noexcept;
    void max_load_factor(float val);
    void rehash(size_t n);
  private:
    DynamicArray< Slot< Key, Value > > table_;
    size_t size_;
    Hash hasher_;
    Equal equal_;
    float max_load_factor_ ;
  };
}

#endif

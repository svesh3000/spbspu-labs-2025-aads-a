// --- ConstIteratorHashTable.hpp ---
#ifndef CONST_ITERATOR_HASH_TABLE_HPP
#define CONST_ITERATOR_HASH_TABLE_HPP

#include <cassert>
#include <iterator>  // Required for std::forward_iterator_tag if you keep the base class
#include <utility>   // Required for std::pair and std::addressof

// Forward declarations for HashTable and IteratorHashTable
namespace gavrilova {
  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  class HashTable;

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  class IteratorHashTable;
}

namespace gavrilova {

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  struct ConstIteratorHashTable /* : public std::iterator< std::forward_iterator_tag, const std::pair< Key, Value > > */ {
    // Standard iterator typedefs (replacing std::iterator base class)
    using iterator_category = std::forward_iterator_tag;
    using value_type = const std::pair< const Key, Value >;  // Already correct
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type*;
    using reference = const value_type&;

    // Friend declarations for access to private members of HashTable and IteratorHashTable
    friend class HashTable< Key, Value, Hash, KeyEqual >;
    friend struct IteratorHashTable< Key, Value, Hash, KeyEqual >;

    using this_t = ConstIteratorHashTable< Key, Value, Hash, KeyEqual >;
    using Table = gavrilova::HashTable< Key, Value, Hash, KeyEqual >;

    // Constructors/Destructors/Assignment Operators
    ConstIteratorHashTable();
    ~ConstIteratorHashTable() = default;
    ConstIteratorHashTable(const this_t&) = default;
    this_t& operator=(const this_t&) = default;

    // Conversion constructor from non-const iterator
    ConstIteratorHashTable(const IteratorHashTable< Key, Value, Hash, KeyEqual >& other);

    // Increment operators
    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;

    // Dereference operators (KEY CHANGES HERE)
    reference operator*() const;
    pointer operator->() const;

    // Comparison operators
    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

    bool operator==(const IteratorHashTable< Key, Value, Hash, KeyEqual >& other) const;
    bool operator!=(const IteratorHashTable< Key, Value, Hash, KeyEqual >& other) const;

  private:
    const Table* table_;  // Pointer to const Table
    size_t index_;

    // Private constructor for HashTable to create const iterators
    explicit ConstIteratorHashTable(const Table* table, size_t index);
  };

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::ConstIteratorHashTable():
    table_(nullptr),
    index_(0)
  {}

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::ConstIteratorHashTable(const Table* table, size_t index):
    table_(table),
    index_(index)
  {}

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::ConstIteratorHashTable(
      const IteratorHashTable< Key, Value, Hash, KeyEqual >& other):
    table_(other.table_),  // Copy the pointer
    index_(other.index_)
  {}

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::this_t&
  ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator++() noexcept
  {
    assert(table_ != nullptr);
    // Use table_->find_next_occupied to skip EMPTY and DELETED slots
    index_ = table_->find_next_occupied(index_ + 1);
    return *this;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::this_t
  ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator++(int) noexcept
  {
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::reference
  ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator*() const
  {
    assert(table_ != nullptr);
    assert(index_ < table_->buckets_.size() && table_->buckets_[index_].state_ == Table::SlotState::OCCUPIED);
    // --- KEY CHANGE: Use get_value_ptr() ---
    return *table_->buckets_[index_].get_value_ptr();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::pointer
  ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator->() const
  {
    assert(table_ != nullptr);
    assert(index_ < table_->buckets_.size() && table_->buckets_[index_].state_ == Table::SlotState::OCCUPIED);
    // --- KEY CHANGE: Use get_value_ptr() ---
    return table_->buckets_[index_].get_value_ptr();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator==(const this_t& rhs) const
  {
    return table_ == rhs.table_ && index_ == rhs.index_;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator!=(const this_t& rhs) const
  {
    return !(*this == rhs);
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator==(
      const IteratorHashTable< Key, Value, Hash, KeyEqual >& other) const
  {
    return table_ == other.table_ && index_ == other.index_;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool ConstIteratorHashTable< Key, Value, Hash, KeyEqual >::operator!=(
      const IteratorHashTable< Key, Value, Hash, KeyEqual >& other) const
  {
    return !(*this == other);
  }
}

#endif  // CONST_ITERATOR_HASH_TABLE_HPP

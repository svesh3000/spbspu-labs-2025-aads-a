// --- IteratorHashTable.hpp ---
#ifndef ITERATOR_HASH_TABLE_HPP
#define ITERATOR_HASH_TABLE_HPP

#include <cassert>
#include <iterator>  // Required for std::forward_iterator_tag if you keep the base class
#include <utility>   // Required for std::pair and std::addressof

// Forward declarations for HashTable and ConstIteratorHashTable
namespace gavrilova {
  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  class HashTable;

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  class ConstIteratorHashTable;
}

namespace gavrilova {

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  struct IteratorHashTable /* : public std::iterator< std::forward_iterator_tag, std::pair< const Key, Value > > */ {
    // Standard iterator typedefs (replacing std::iterator base class)
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair< const Key, Value >;  // Corrected to match HashTable's value_type
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using reference = value_type&;

    // Friend declarations for access to private members of HashTable and ConstIteratorHashTable
    friend class HashTable< Key, Value, Hash, KeyEqual >;
    friend struct ConstIteratorHashTable< Key, Value, Hash, KeyEqual >;

    using this_t = IteratorHashTable< Key, Value, Hash, KeyEqual >;
    using Table = gavrilova::HashTable< Key, Value, Hash, KeyEqual >;

    // Constructors/Destructors/Assignment Operators
    IteratorHashTable();
    ~IteratorHashTable() = default;
    IteratorHashTable(const this_t&) = default;
    this_t& operator=(const this_t&) = default;

    // Increment operators
    this_t& operator++() noexcept;
    this_t operator++(int) noexcept;

    // Dereference operators (KEY CHANGES HERE)
    reference operator*() const;
    pointer operator->() const;

    // Comparison operators
    bool operator!=(const this_t&) const;
    bool operator==(const this_t&) const;

    bool operator!=(const ConstIteratorHashTable< Key, Value, Hash, KeyEqual >& other) const;
    bool operator==(const ConstIteratorHashTable< Key, Value, Hash, KeyEqual >& other) const;

  private:
    Table* table_;
    size_t index_;

    // Private constructor for HashTable to create iterators
    explicit IteratorHashTable(HashTable< Key, Value, Hash, KeyEqual >* table, size_t index);
  };

  template < typename Key, typename Value, typename Hash, typename Equal >
  IteratorHashTable< Key, Value, Hash, Equal >::IteratorHashTable():
    table_(nullptr),
    index_(0)
  {}

  template < typename Key, typename Value, typename Hash, typename Equal >
  IteratorHashTable< Key, Value, Hash, Equal >::IteratorHashTable(HashTable< Key, Value, Hash, Equal >* table, size_t index):
    table_(table),
    index_(index)
  {}

  template < typename Key, typename Value, typename Hash, typename Equal >
  typename IteratorHashTable< Key, Value, Hash, Equal >::this_t&
  IteratorHashTable< Key, Value, Hash, Equal >::operator++() noexcept
  {
    assert(table_ != nullptr);
    // Use table_->find_next_occupied to skip EMPTY and DELETED slots
    index_ = table_->find_next_occupied(index_ + 1);
    return *this;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename IteratorHashTable< Key, Value, Hash, KeyEqual >::this_t
  IteratorHashTable< Key, Value, Hash, KeyEqual >::operator++(int) noexcept
  {
    this_t temp(*this);
    ++(*this);
    return temp;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename IteratorHashTable< Key, Value, Hash, KeyEqual >::reference
  IteratorHashTable< Key, Value, Hash, KeyEqual >::operator*() const
  {
    assert(table_ != nullptr);
    assert(index_ < table_->buckets_.size() && table_->buckets_[index_].state_ == Table::SlotState::OCCUPIED);
    // --- KEY CHANGE: Use get_value_ptr() ---
    return *table_->buckets_[index_].get_value_ptr();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename IteratorHashTable< Key, Value, Hash, KeyEqual >::pointer
  IteratorHashTable< Key, Value, Hash, KeyEqual >::operator->() const
  {
    assert(table_ != nullptr);
    assert(index_ < table_->buckets_.size() && table_->buckets_[index_].state_ == Table::SlotState::OCCUPIED);
    // --- KEY CHANGE: Use get_value_ptr() ---
    return table_->buckets_[index_].get_value_ptr();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool IteratorHashTable< Key, Value, Hash, KeyEqual >::operator==(const this_t& rhs) const
  {
    return table_ == rhs.table_ && index_ == rhs.index_;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool IteratorHashTable< Key, Value, Hash, KeyEqual >::operator!=(const this_t& rhs) const
  {
    return !(*this == rhs);
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool IteratorHashTable< Key, Value, Hash, KeyEqual >::operator==(
      const ConstIteratorHashTable< Key, Value, Hash, KeyEqual >& other) const
  {
    return table_ == other.table_ && index_ == other.index_;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool IteratorHashTable< Key, Value, Hash, KeyEqual >::operator!=(
      const ConstIteratorHashTable< Key, Value, Hash, KeyEqual >& other) const
  {
    return !(*this == other);
  }
}

#endif  // ITERATOR_HASH_TABLE_HPP

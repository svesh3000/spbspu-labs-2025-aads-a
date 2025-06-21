#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <functional>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

// #include "ConstIteratorHashTable.hpp"
// #include "IteratorHashTable.hpp"

namespace {
  bool is_prime(size_t n)
  {
    if (n <= 1) {
      return false;
    }
    if (n <= 3) {
      return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
      return false;
    }

    for (size_t i = 5; i * i <= n; i += 6) {
      if (n % i == 0 || n % (i + 2) == 0) {
        return false;
      }
    }
    return true;
  }

  size_t find_next_prime(size_t n)
  {
    if (n <= 2) {
      return 2;
    }
    if (n % 2 == 0) {
      ++n;
    }

    while (!is_prime(n)) {
      n += 2;
    }
    return n;
  }
}


namespace gavrilova {

  template < typename Key, typename Value, typename Hash = std::hash< Key >, typename KeyEqual = std::equal_to< Key > >
  struct IteratorHashTable;

  template < typename Key, typename Value, typename Hash = std::hash< Key >, typename KeyEqual = std::equal_to< Key > >
  struct ConstIteratorHashTable;

  template < typename Key, typename Value, typename Hash = std::hash< Key >, typename KeyEqual = std::equal_to< Key > >
  class HashTable {
  public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair< const Key, Value >;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using hasher = Hash;
    using key_equal = KeyEqual;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = gavrilova::IteratorHashTable< Key, Value, Hash, KeyEqual >;
    using const_iterator = gavrilova::ConstIteratorHashTable< Key, Value, Hash, KeyEqual >;

    explicit HashTable(size_type initial_buckets = 19);
    HashTable(std::initializer_list< value_type > init_list);
    template < typename InputIt >
    HashTable(InputIt first, InputIt last);
    ~HashTable();

    std::pair< iterator, bool > insert(const value_type& value);
    std::pair< iterator, bool > insert(value_type&& value);

    template < typename InputIt >
    void insert(InputIt first, InputIt last);

    template < typename... Args >
    std::pair< iterator, bool > emplace(Args&&... args);

    size_type erase(const Key& key);
    iterator erase(const_iterator pos);

    void clear() noexcept;
    void swap(HashTable& other) noexcept;

    Value& at(const Key& key);
    const Value& at(const Key& key) const;

    Value& operator[](const Key& key);
    Value& operator[](Key&& key);

    iterator find(const Key& key);
    const_iterator find(const Key& key) const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type bucket_count() const noexcept;

    float load_factor() const noexcept;
    float max_load_factor() const noexcept;
    void max_load_factor(float ml);

    void rehash(size_type count);

  private:
    enum class SlotState {
      EMPTY,
      OCCUPIED,
      DELETED
    };

    struct Slot {
      union {
        value_type value_;
      };
      SlotState state_ = SlotState::EMPTY;

      Slot();
      ~Slot();
      void destroy();
    };

    std::vector< Slot > buckets_;
    size_type element_count_;
    float max_load_factor_;
    Hash hasher_;
    KeyEqual key_equal_;

    std::pair< size_type, bool > find_slot_for_insert(const Key& key) const;
    std::pair< size_type, bool > find_slot_for_read(const Key& key) const;
    size_type find_next_occupied(size_type start_index) const;
  };



  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::Slot::Slot()
  {}

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::Slot::~Slot()
  {}

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::Slot::destroy()
  {
    if (state_ == SlotState::OCCUPIED) {
      value_.~value_type();
    }
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(size_type initial_buckets):
    buckets_(::find_next_prime(initial_buckets)),
    element_count_(0),
    max_load_factor_(0.75f),
    hasher_(),
    key_equal_()
  {}

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(std::initializer_list< value_type > init_list):
    HashTable(init_list.size() * 2)
  {
    insert(init_list.begin(), init_list.end());
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  template < typename InputIt >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(InputIt first, InputIt last):
    HashTable(std::distance(first, last) * 2)
  {
    insert(first, last);
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::~HashTable()
  {
    clear();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  std::pair< typename HashTable< Key, Value, Hash, KeyEqual >::iterator, bool >
  HashTable< Key, Value, Hash, KeyEqual >::insert(const value_type& value)
  {
    return emplace(value);
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  std::pair< typename HashTable< Key, Value, Hash, KeyEqual >::iterator, bool >
  HashTable< Key, Value, Hash, KeyEqual >::insert(value_type&& value)
  {
    return emplace(std::move(value));
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  template < typename InputIt >
  void HashTable< Key, Value, Hash, KeyEqual >::insert(InputIt first, InputIt last)
  {
    for (auto it = first; it != last; ++it) {
      insert(*it);
    }
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  template < typename... Args >
  std::pair< typename HashTable< Key, Value, Hash, KeyEqual >::iterator, bool >
  HashTable< Key, Value, Hash, KeyEqual >::emplace(Args&&... args)
  {
    value_type temp_pair(std::forward< Args >(args)...);
    const Key& key = temp_pair.first;

    if (load_factor() >= max_load_factor_) {
      rehash(buckets_.size() * 2);
    }

    auto pair = find_slot_for_read(key);
    size_type index = pair.first;
    bool found = pair.second;

    if (found) {
      return {iterator(this, index), false};
    }

    new (&buckets_[index].value_) value_type(std::forward< Args >(args)...);
    buckets_[index].state_ = SlotState::OCCUPIED;
    element_count_++;

    return {iterator(this, index), true};
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::size_type
  HashTable< Key, Value, Hash, KeyEqual >::erase(const Key& key)
  {
    auto it = find(key);
    if (it == end()) {
      return 0;
    }
    erase(it);
    return 1;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::iterator
  HashTable< Key, Value, Hash, KeyEqual >::erase(const_iterator pos)
  {
    if (pos == cend() || buckets_[pos.index_].state_ != SlotState::OCCUPIED) {
      return end();
    }

    buckets_[pos.index_].destroy();
    buckets_[pos.index_].state_ = SlotState::DELETED;
    element_count_--;

    auto next_it = iterator(this, pos.index_);
    ++next_it;
    return next_it;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::clear() noexcept
  {
    for (size_type i = 0; i < buckets_.size(); ++i) {
      buckets_[i].destroy();
      buckets_[i].state_ = SlotState::EMPTY;
    }
    element_count_ = 0;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::swap(HashTable& other) noexcept
  {
    std::swap(buckets_, other.buckets_);
    std::swap(element_count_, other.element_count_);
    std::swap(max_load_factor_, other.max_load_factor_);
    std::swap(hasher_, other.hasher_);
    std::swap(key_equal_, other.key_equal_);
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  Value& HashTable< Key, Value, Hash, KeyEqual >::at(const Key& key)
  {
    auto it = find(key);
    if (it == end()) {
      throw std::out_of_range("HashTable::at: key not found");
    }
    return it->second;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  const Value& HashTable< Key, Value, Hash, KeyEqual >::at(const Key& key) const
  {
    auto it = find(key);
    if (it == cend()) {
      throw std::out_of_range("HashTable::at: key not found");
    }
    return it->second;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  Value& HashTable< Key, Value, Hash, KeyEqual >::operator[](const Key& key)
  {
    return emplace(key, Value{}).first->second;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  Value& HashTable< Key, Value, Hash, KeyEqual >::operator[](Key&& key)
  {
    return emplace(std::move(key), Value{}).first->second;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::iterator
  HashTable< Key, Value, Hash, KeyEqual >::find(const Key& key)
  {
    auto pair = find_slot_for_read(key);
    size_type index = pair.first;
    bool found = pair.second;
    return found ? iterator(this, index) : end();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::const_iterator
  HashTable< Key, Value, Hash, KeyEqual >::find(const Key& key) const
  {
    auto pair = find_slot_for_read(key);
    size_type index = pair.first;
    bool found = pair.second;
    return found ? const_iterator(this, index) : cend();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::iterator
  HashTable< Key, Value, Hash, KeyEqual >::begin()
  {
    return iterator(this, find_next_occupied(0));
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::iterator
  HashTable< Key, Value, Hash, KeyEqual >::end()
  {
    return iterator(this, buckets_.size());
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::const_iterator
  HashTable< Key, Value, Hash, KeyEqual >::begin() const
  {
    return cbegin();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::const_iterator
  HashTable< Key, Value, Hash, KeyEqual >::end() const
  {
    return cend();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::const_iterator
  HashTable< Key, Value, Hash, KeyEqual >::cbegin() const
  {
    return const_iterator(this, find_next_occupied(0));
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::const_iterator
  HashTable< Key, Value, Hash, KeyEqual >::cend() const
  {
    return const_iterator(this, buckets_.size());
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  bool HashTable< Key, Value, Hash, KeyEqual >::empty() const noexcept
  {
    return element_count_ == 0;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::size_type
  HashTable< Key, Value, Hash, KeyEqual >::size() const noexcept
  {
    return element_count_;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::size_type
  HashTable< Key, Value, Hash, KeyEqual >::bucket_count() const noexcept
  {
    return buckets_.size();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  float HashTable< Key, Value, Hash, KeyEqual >::load_factor() const noexcept
  {
    return buckets_.empty() ? 0.0f : static_cast< float >(element_count_) / buckets_.size();
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  float HashTable< Key, Value, Hash, KeyEqual >::max_load_factor() const noexcept
  {
    return max_load_factor_;
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::max_load_factor(float ml)
  {
    max_load_factor_ = ml;
    if (load_factor() >= max_load_factor_) {
      rehash(buckets_.size());
    }
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::rehash(size_type count)
  {
    size_type new_size = ::find_next_prime(std::max(count,
        static_cast< size_type >(element_count_ / max_load_factor_)));
    if (new_size <= buckets_.size()) {
      return;
    }

    std::vector< Slot > new_buckets(new_size);
    HashTable temp_table;
    temp_table.buckets_.swap(new_buckets);

    for (auto it = begin(); it != end(); ++it) {
      temp_table.emplace(std::move(it->first), std::move(it->second));
    }

    buckets_.swap(temp_table.buckets_);
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  std::pair< typename HashTable< Key, Value, Hash, KeyEqual >::size_type, bool >
  HashTable< Key, Value, Hash, KeyEqual >::find_slot_for_insert(const Key& key) const
  {
    size_t hash = hasher_(key);
    size_t index = hash % buckets_.size();
    size_t first_deleted = buckets_.size();

    for (size_t i = 0; i < buckets_.size(); ++i) {
      size_t current = (index + i) % buckets_.size();

      if (buckets_[current].state_ == SlotState::EMPTY) {
        return {first_deleted != buckets_.size() ? first_deleted : current, false};
      }

      if (buckets_[current].state_ == SlotState::OCCUPIED &&
          key_equal_(buckets_[current].value_.first, key)) {
        return {current, true};
      }

      if (buckets_[current].state_ == SlotState::DELETED && first_deleted == buckets_.size()) {
        first_deleted = current;
      }
    }

    return {first_deleted != buckets_.size() ? first_deleted : 0, false};
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  std::pair< typename HashTable< Key, Value, Hash, KeyEqual >::size_type, bool >
  HashTable< Key, Value, Hash, KeyEqual >::find_slot_for_read(const Key& key) const
  {
    size_t hash = hasher_(key);
    size_t index = hash % buckets_.size();

    for (size_t i = 0; i < buckets_.size(); ++i) {
      size_t current = (index + i) % buckets_.size();

      if (buckets_[current].state_ == SlotState::EMPTY) {
        return {0, false};
      }

      if (buckets_[current].state_ == SlotState::OCCUPIED &&
          key_equal_(buckets_[current].value_.first, key)) {
        return {current, true};
      }
    }

    return {0, false};
  }

  template < typename Key, typename Value, typename Hash, typename KeyEqual >
  typename HashTable< Key, Value, Hash, KeyEqual >::size_type
  HashTable< Key, Value, Hash, KeyEqual >::find_next_occupied(size_type start_index) const
  {
    for (size_t i = start_index; i < buckets_.size(); ++i) {
      if (buckets_[i].state_ == SlotState::OCCUPIED) {
        return i;
      }
    }
    return buckets_.size();
  }

}

#endif

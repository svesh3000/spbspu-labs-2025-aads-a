#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <functional>
//#include <dynamic_array.hpp>
#include <vector>
#include "hash_table_iterator.hpp"

namespace demehin
{
  template < typename Key, typename T, typename Hash = std::hash< Key >, typename Equal = std::equal_to< Key > >
  class HashTable
  {
    friend class HashTIterator< Key, T, Hash, Equal, false >;
    friend class HashTIterator< Key, T, Hash, Equal, true >;
  public:
    using Iter = HashTIterator< Key, T, Hash, Equal, false >;
    using cIter = HashTIterator< Key, T, Hash, Equal, true >;

    HashTable() noexcept;

    std::pair< Iter, bool > insert(const std::pair< Key, T >&);

    T& operator[](const Key&);

    size_t erase(const Key&);
    Iter erase(cIter);

    T& at(const Key&);
    const T& at(const Key&) const;

    Iter find(const Key&);
    cIter find(const Key&) const;

    void rehash(size_t);
    double load_factor() const noexcept;

    Iter begin() noexcept;
    Iter end() noexcept;
    cIter cbegin() const noexcept;
    cIter cend() const noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    enum class SlotState
    {
      EMPTY,
      OCCUPIED,
      DELETED
    };

    struct Slot
    {
      std::pair< Key, T > pair;
      SlotState state = SlotState::EMPTY;
    };

    std::vector< Slot > slots_;
    size_t item_cnt_;
    Hash hasher_;
    Equal equal_;
    static constexpr double max_load_factor_ = 0.7;

    size_t findKey(const Key&) const;
    size_t findSlot(const Key&) const;
    size_t findSlotIn(const Key&, const std::vector< Slot >&) const noexcept;

  };

  template< typename Key, typename T, typename Hash, typename Equal >
  HashTable< Key, T, Hash, Equal >::HashTable() noexcept:
    slots_(16),
    item_cnt_(0)
  {}

  template< typename Key, typename T, typename Hash, typename Equal >
  size_t HashTable< Key, T, Hash, Equal >::findKey(const Key& key) const
  {
    size_t hash_val = hasher_(key) % slots_.size();
    size_t ind = hash_val;
    size_t i = 1;

    while (slots_[ind].state != SlotState::EMPTY)
    {
      if (slots_[ind].state == SlotState::OCCUPIED && equal_(slots_[ind].pair.first, key))
      {
        return ind;
      }
      ind = (hash_val + i * i) % slots_.size();
      i++;

      if (i > slots_.size())
      {
        break;
      }
    }
    return slots_.size();
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  size_t HashTable< Key, T, Hash, Equal >::findSlot(const Key& key) const
  {
    size_t hash_val = hasher_(key) % slots_.size();
    size_t first_deleted = slots_.size();
    size_t ind = hash_val;
    size_t i = 1;

    while (slots_[ind].state != SlotState::EMPTY)
    {
      if (slots_[ind].state == SlotState::OCCUPIED && equal_(slots_[ind].pair.first, key))
      {
        return ind;
      }

      if (slots_[ind].state == SlotState::DELETED && first_deleted != slots_.size())
      {
        first_deleted = ind;
      }

      ind = (hash_val + i * i) % slots_.size();
      i++;

      if (i > slots_.size())
      {
        break;
      }
    }
    return (first_deleted != slots_.size()) ? first_deleted : ind;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  size_t HashTable< Key, T, Hash, Equal >::findSlotIn(const Key& key, const std::vector< Slot >& target) const noexcept
  {
    size_t hash_val = hasher_(key) % target.size();
    size_t ind = hash_val;
    size_t i = 1;

    while (target[ind].state == SlotState::OCCUPIED)
    {
      ind = (hash_val + i * i) % target.size();
      i++;
    }
    return ind;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  void HashTable< Key, T, Hash, Equal >::rehash(size_t new_size)
  {
    if (new_size < item_cnt_ / max_load_factor_)
    {
      new_size = static_cast< size_t >(item_cnt_ / max_load_factor_) + 1;
    }
    if (new_size <= slots_.size())
    {
      return;
    }

    std::vector< Slot > new_slots(new_size);
    for (auto& slot : slots_)
    {
      if (slot.state == SlotState::OCCUPIED)
      {
        size_t ind = findSlotIn(slot.pair.first, new_slots);
        new_slots[ind] = slot;
        new_slots[ind].state = SlotState::OCCUPIED;
      }
    }
    slots_ = std::move(new_slots);
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  double HashTable< Key, T, Hash, Equal >::load_factor() const noexcept
  {
    return static_cast< double >(item_cnt_) / slots_.size();
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  size_t HashTable< Key, T, Hash, Equal >::size() const noexcept
  {
    return item_cnt_;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  bool HashTable< Key, T, Hash, Equal >::empty() const noexcept
  {
    return item_cnt_ == 0;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  std::pair< typename HashTable< Key, T, Hash, Equal >::Iter, bool > HashTable< Key, T, Hash, Equal >::insert(const std::pair< Key, T >& val)
  {
    if (load_factor() >= max_load_factor_)
    {
      rehash(slots_.size() * 2);
    }

    size_t ind = findSlot(val.first);
    if (slots_[ind].state == SlotState::OCCUPIED)
    {
      return std::make_pair(Iter(this, ind), false);
    }

    slots_[ind].pair = val;
    slots_[ind].state = SlotState::OCCUPIED;
    item_cnt_++;
    return std::make_pair(Iter(this, ind), true);
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  T& HashTable< Key, T, Hash, Equal >::operator[](const Key& key)
  {
    auto res = insert(std::make_pair(key, T()));
    return res.first->second;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  T& HashTable< Key, T, Hash, Equal >::at(const Key& key)
  {
    size_t ind = findKey(key);
    if (ind == slots_.size())
    {
      throw std::logic_error("key not found");
    }

    return slots_[ind].pair.second;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  const T& HashTable< Key, T, Hash, Equal >::at(const Key& key) const
  {
    size_t ind = find_key(key);
    if (ind == slots_.size())
    {
      throw std::logic_error("key not found");
    }

    return slots_[ind].pair.second;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  typename HashTable< Key, T, Hash, Equal >::Iter HashTable< Key, T, Hash, Equal >::begin() noexcept
  {
    return Iter(this, 0);
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  typename HashTable< Key, T, Hash, Equal >::Iter HashTable< Key, T, Hash, Equal >::end() noexcept
  {
    return Iter(this, slots_.size());
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  typename HashTable< Key, T, Hash, Equal >::cIter HashTable< Key, T, Hash, Equal >::cbegin() const noexcept
  {
    return cIter(this, 0);
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  typename HashTable< Key, T, Hash, Equal >::cIter HashTable< Key, T, Hash, Equal >::cend() const noexcept
  {
    return cIter(this, slots_.size());
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  typename HashTable< Key, T, Hash, Equal >::Iter HashTable< Key, T, Hash, Equal >::find(const Key& key)
  {
    size_t ind = findKey(key);
    return (ind == slots_.size()) ? end() : Iter(this, ind);
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  typename HashTable< Key, T, Hash, Equal >::cIter HashTable< Key, T, Hash, Equal >::find(const Key& key) const
  {
    size_t ind = findKey(key);
    return (ind == slots_.size()) ? cend() : cIter(this, ind);
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  size_t HashTable< Key, T, Hash, Equal >::erase(const Key& key)
  {
    size_t ind = findKey(key);
    if (ind == slots_.size())
    {
      return 0;
    }

    slots_[ind].state = SlotState::DELETED;
    item_cnt_--;
    return 1;
  }

  template< typename Key, typename T, typename Hash, typename Equal >
  typename HashTable< Key, T, Hash, Equal >::Iter HashTable< Key, T, Hash, Equal >::erase(cIter pos)
  {
    slots_[pos.index_].state = SlotState::DELETED;
    item_cnt_--;
    Iter next(this, pos.index_);
    return ++next;
  }
}

#endif

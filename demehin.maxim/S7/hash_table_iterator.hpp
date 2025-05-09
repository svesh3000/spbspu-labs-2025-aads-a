#ifndef HASH_TABLE_ITERATOR
#define HASH_TABLE_ITERATOR
#include "hash_table.hpp"

namespace demehin
{
  template< typename Key, typename T, typename Hash, typename Equal >
  class HashTable;

  template< typename Key, typename T, typename Hash, typename Equal, bool isConst >
  class HashTIterator
  {
    friend class HashTable< Key, T, Hash, Equal >;
    friend class HashTIterator< Key, T, Hash, Equal, true >;
    friend class HashTIterator< Key, T, Hash, Equal, false >;
  public:
    using this_t = HashTIterator< Key, T, Hash, Equal, isConst >;
    using Val = typename std::conditional_t< isConst, const std::pair< Key, T >, std::pair< Key, T > >;
    using Ref = typename std::conditional_t< isConst, const std::pair< Key, T >&, std::pair< Key, T >& >;
    using Ptr = typename std::conditional_t< isConst, const std::pair< Key, T >*, std::pair< Key, T >* >;
    using Table = HashTable< Key, T, Hash, Equal >;

    HashTIterator() noexcept:
      table_(nullptr),
      index_(0)
    {}

    this_t& operator++() noexcept
    {
      ++index_;
      skipEmpty();
      return *this;
    }

    this_t operator++(int) noexcept
    {
      this_t tmp = *this;
      ++(*this);
      return tmp;
    }

    Ref operator*() const noexcept
    {
      return table_->slots_[index_].pair;
    }

    Ptr operator->() const noexcept
    {
      return &table_->slots_[index_].pair;
    }

    bool operator==(const this_t& rhs) const noexcept
    {
      return table_ == rhs.table_ && index_ == rhs.index_;
    }

    bool operator!=(const this_t& rhs) const noexcept
    {
      return !(*this == rhs);
    }

  private:
    HashTIterator(Table* table, size_t index) noexcept:
      table_(table),
      index_(index)
    {
      skipEmpty();
    }

    void skipEmpty() noexcept
    {
      while (index_ < table_->slots_.size() && table_->slots_[index_].state_ != HashTable< Key, T, Hash, Equal >::SlotState::OCCUPIED)
      {
        ++index_;
      }
    }

    Table* table_;
    size_t index_;
  };
}

#endif

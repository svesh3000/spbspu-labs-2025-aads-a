#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <functional>
#include <dynamic_array.hpp>
#include "hash_iter.hpp"
#include "hash_citer.hpp"

namespace tkach
{
  template< class Key, class Value, class Hash = std::hash< Key >, class Equal = std::equal_to< Key > >
  class HashTable
  {
  public:
    using Iter = HashIterator< Key, Value, Hash, Equal >;
    using CIter = CHashIterator< Key, Value, Hash, Equal >;
    using pair_t = std::pair< HashIterator< Key, Value, Hash, Equal >, bool >;
    HashTable();
    template< class InputIt >
    HashTable(InputIt begin, InputIt end);
    HashTable(std::initializer_list< std::pair< Key, Value > > init_list);
    HashTable(size_t size);
    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;
    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    CIter cend();
    CIter cbegin();
    Iter end();
    Iter begin();
    size_t size() const noexcept;
    bool empty() const noexcept;
    pair_t insert(const std::pair< Key, Value >& pair);
    pair_t insert(std::pair< Key, Value >&& pair);
    Iter insert(CIter, const Key&);
    template< class InputIt >
    void insert(InputIt first, InputIt last);
    size_t erase(const Key& key);
    Iter find(const Key& key);
    CIter find(const Key& key) const;
    Iter erase(Iter it);
    Iter erase(CIter it);
    Iter erase(CIter first, CIter last);
    void rehash(size_t new_size);
    float maxLoadFactor() const;
    void maxLoadFactor(float ml);
    float load_factor() const;
  private:
    enum class EntryState
    {
      Empty,
      Occupied,
      Deleted
    };
    struct Slot
    {
      std::pair< Key, Value > pair;
      EntryState state = EntryState::Empty;
    };
    DynArray< Slot > table_;
    size_t count_;
    Hash hasher_;
    Equal key_equal_;
    float max_load_factor = 0.7;
    template< class... Args >
    pair_t emplace(Args&&... args);
    size_t fins_pos(const Key& key);
  };

  template< class Key, class Value, class Hash, class Equal >
  HashTable<Key, Value, Hash, Equal >::HashTable():
    table_(11),
    count_(0)
  {}

  template< class Key, class Value, class Hash, class Equal >
  HashTable<Key, Value, Hash, Equal >::HashTable(size_t size):
    table_(size),
    count_(0)
  {}

  template< class Key, class Value, class Hash, class Equal >
  template< class InputIt >
  HashTable<Key, Value, Hash, Equal >::HashTable(InputIt begin, InputIt end):
    HashTable()
  {
    insert(begin, end);
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable<Key, Value, Hash, Equal >::HashTable(std::initializer_list< std::pair< Key, Value > > init_list):
    HashTable(init_list.begin(), init_list.end())
  {}

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable<Key, Value, Hash, Equal >::size() const noexcept
  {
    return count_;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable<Key, Value, Hash, Equal >::empty() const noexcept
  {
    return count_ == 0;
  }

  template< class Key, class Value, class Hash, class Equal >
  CHashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::cend()
  {
    return CIter{this, table_.size()};
  }

  template< class Key, class Value, class Hash, class Equal >
  CHashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::cbegin()
  {
    return CIter{this, 0};
  }

  template< class Key, class Value, class Hash, class Equal >
  HashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::end()
  {
    return Iter{this, table_.size()};
  }

  template< class Key, class Value, class Hash, class Equal >
  HashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::begin()
  {
    return Iter{this, 0};
  }

  template< class Key, class Value, class Hash, class Equal >
  auto HashTable<Key, Value, Hash, Equal >::insert(const std::pair< Key, Value >& pair) -> pair_t
  {
    return emplace(pair);
  }

  template< class Key, class Value, class Hash, class Equal >
  auto HashTable<Key, Value, Hash, Equal >::insert(std::pair< Key, Value >&& pair) -> pair_t
  {
    return emplace(std::move(pair));
  }

  template< class Key, class Value, class Hash, class Equal >
  HashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::insert(CIter cit, const Key& key)
  {

  }

  template< class Key, class Value, class Hash, class Equal >
  template< class InputIt >
  void HashTable<Key, Value, Hash, Equal >::insert(InputIt first, InputIt last)
  {
  
  }

  template< class Key, class Value, class Hash, class Equal >
  template< class... Args >
  auto HashTable<Key, Value, Hash, Equal >::emplace(Args&&... args) -> pair_t
  {
    if (((count_ + 1) * 1.0) / table_.size() >= max_load_factor)
    {
      rehash(table_.size() * 2 + 1);
    }
    std::pair< Key, Value > pair(std::forward< Args >(args)...);
    size_t pos = find_pos(pair.first);
    if (table_[pos].state == EntryState::Occupied)
    {
      return {HashIterator<Key, Value, Hash, Equal >{this, pos}, false};
    }
    table_[pos].pair = std::move(pair);
    table_[pos].state = EntryState::Occupied;
    count_++;
    return {HashIterator<Key, Value, Hash, Equal >{this, pos}, true};
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable<Key, Value, Hash, Equal >::fins_pos(const Key& key)
  {
    size_t initial_index = hasher_(key) % table_.size();
    size_t first_deleted = table_.size();
    for (size_t i = 0; i < table_.size(); ++i)
    {
      size_t cur_index = (initial_index + i * i) % table_.size();
      if (table_[cur_index].state == EntryState::Occupied)
      {
        if (key_equal_(table_[cur_index].pair.first, key))
        {
          return cur_index;
        }
      }
      else if (table_[cur_index].state == EntryState::Deleted)
      {
        if (first_deleted == table_.size())
        {
          first_deleted = cur_index;
        }
      }
      else
      {
        return (first_deleted != -1) ? first_deleted : cur_index;
      }
    }
    return first_deleted;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable<Key, Value, Hash, Equal >::rehash(size_t new_size)
  {
    if (new_size < count_)
    {
      new_size = count_ * 2 + 1;
    }
    DynArray< Slot > new_table(new_size);
    for (size_t i = 0; i < table_.size(); ++i)
    {
      size_t new_index = find_pos(table_[i].pair.first);
      new_table[new_index].pair = table_[i].pair;
      new_table[new_index].state = EntryState::Occupied;
    }
    table_ = std::move(new_table);
  }

  template< class Key, class Value, class Hash, class Equal >
  size_t HashTable<Key, Value, Hash, Equal >::erase(const Key& key)
  {
    CIter it = find(key);
    if (it != end())
    {
      erase(it);
      return 1;
    }
    return 0;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::erase(Iter it)
  {
    return erase(CIter(it));
  }

  template< class Key, class Value, class Hash, class Equal >
  HashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::erase(CIter it)
  {
    if (table_[it.pos_].state == EntryState::Deleted && table_[it.pos_].state == EntryState::Empty)
    {
      return ++it;
    }
    table_[it.pos_].status = EntryState::Deleted;
    --count_;
    ++it;
    return Iter{this, it.pos_};

  }

  template< class Key, class Value, class Hash, class Equal >
  HashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::erase(CIter first, CIter last)
  {
    while (first != last)
    {
      first = erase(first);
    }
    return first;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::find(const Key& key)
  {
    return Iter(static_cast< const HashTable< Key, Value, Hash, Equal >* >(this)->find(key));
  }

  template< class Key, class Value, class Hash, class Equal >
  CHashIterator< Key, Value, Hash, Equal > HashTable<Key, Value, Hash, Equal >::find(const Key& key) const
  {
    size_t initial_index = hasher_(key) % table_.size();
    size_t first_deleted = table_.size();
    for (size_t i = 0; i < table_.size(); ++i)
    {
      size_t cur_index = (initial_index + i * i) % table_.size();
      if (table_[cur_index].state == EntryState::Occupied)
      {
        if (key_equal_(table_[cur_index].pair.first, key))
        {
          return CIter{this, cur_index};
        }
      }
      else if (table_[cur_index].state == EntryState::Empty)
      {
        return cend();
      }
    }
    return cend();   
  }

  template< class Key, class Value, class Hash, class Equal >
  Value& HashTable<Key, Value, Hash, Equal >::operator[](const Key& key)
  {
    Iter it = find(key);
    if (it == end())
    {
      it = insert(std::make_pair(key, Value()));
    }
    return node->second;
  }

  template< class Key, class Value, class Hash, class Equal >
  const Value& HashTable<Key, Value, Hash, Equal >::operator[](const Key& key) const
  {
    CIter cit = find(key);
    return cit->second;
  }

  template< class Key, class Value, class Hash, class Equal >
  Value& HashTable<Key, Value, Hash, Equal >::at(const Key& key)
  {
    return const_cast< Value& >(static_cast< const HashTable<Key, Value, Hash, Equal >* >(this)->at(key));
  }

  template< class Key, class Value, class Hash, class Equal >
  const Value& HashTable<Key, Value, Hash, Equal >::at(const Key& key) const
  {
    CIter it = find(key);
    if (it != cend())
    {
      return node->second;
    }
    throw std::out_of_range("<INVALID COMMAND>");
  }

  template< class Key, class Value, class Hash, class Equal >
  float HashTable<Key, Value, Hash, Equal >::maxLoadFactor() const
  {
    return max_load_factor;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable<Key, Value, Hash, Equal >::maxLoadFactor(float ml)
  {
    if (ml <= 0.1f || ml >= 0.95f)
    {
      throw std::invalid_argument("Invalid load factor");
    }
    max_load_factor = ml;
    if (load_factor >= max_load_factor)
    {
      rehash(2 * table_.size() + 1);
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  float HashTable<Key, Value, Hash, Equal >::load_factor() const
  {
    return table.empty() ? 0.0f : static_cast< float >(count_) / table_.size();
  }
}
#endif

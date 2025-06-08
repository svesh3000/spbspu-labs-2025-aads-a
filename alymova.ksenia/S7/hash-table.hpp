#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <functional>
#include "hash-node.hpp"
#include "hash-iterators.hpp"

namespace alymova
{
  template< class Key, class Value, class Hash = std::hash< Key >, class KeyEqual = std::equal_to< Key > >
  class HashTable
  {
  public:
    using Hashtable = HashTable< Key, Value, Hash, KeyEqual >;
    using Iterator = HashIterator< Key, Value, Hash, KeyEqual >;
    using ConstIterator = HashConstIterator< Key, Value, Hash, KeyEqual >;
    using Node = detail::HashNode< Key, Value >;
    enum NodeType: int {Empty, Fill};

    using ValueType = std::pair< Key, Value >;
    using T = std::pair< NodeType, Node >;

    HashTable();
    HashTable(const HashTable& other);
    HashTable(HashTable&& other) noexcept;
    template< class InputIterator >
    HashTable(InputIterator first, InputIterator last);
    HashTable(std::initializer_list< T > il);
    ~HashTable() noexcept;

    HashTable& operator=(const HashTable& other);
    HashTable& operator=(HashTable&& other) noexcept;

    Iterator begin() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator cbegin() const noexcept;
    Iterator end() noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cend() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    Iterator insert(const ValueType& value);
    Iterator insert(ValueType&& value);

    size_t erase(const Key& key);
    Iterator erase(Iterator pos);
    Iterator erase(ConstIterator pos);

    Iterator find(const Key& key);
    ConstIterator find(const Key& key) const;

    float load_factor() const noexcept;
    float max_load_factor() const noexcept;
    void max_load_factor(float mlf) noexcept; //resixe if new mlf

    void clear() noexcept;
    void swap(HashTable& other);
  private:
    float max_load_factor_ = 0.7;
    size_t size_;
    size_t capacity_;
    T* array_;
    Hash hasher;

    std::pair< bool, T > robRich(const ValueType& value, size_t home_slot);
  };

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable():
    size_(0),
    capacity_(11),
    array_(new T[capacity_]()),
    hasher()
  {
    clear();
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::~HashTable() noexcept
  {
    delete[] array_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >& HashTable< Key, Value, Hash, KeyEqual >::operator=(const HashTable& other)
  {
    HashTable copy(other);
    swap(copy);
    return *this;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >& HashTable< Key, Value, Hash, KeyEqual >::operator=(HashTable&& other) noexcept
  {
    HashTable movy(std::move(other));
    swap(movy);
    return *this;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::begin() noexcept
  {
    ConstIterator it = cbegin();
    return Iterator{it.node_, it.end_};
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::begin() const noexcept
  {
    return cbegin();
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::cbegin() const noexcept
  {
    ConstIterator it(array_, array_ + capacity_);
    T* tmp = array_;
    if (array_->first == NodeType::Empty)
    {
      ++it;
    }
    return it;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::end() noexcept
  {
    return Iterator(array_ + capacity_, array_ + capacity_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::end() const noexcept
  {
    return cend();
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::cend() const noexcept
  {
    return ConstIterator(array_ + capacity_, array_ + capacity_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  bool HashTable< Key, Value, Hash, KeyEqual >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  size_t HashTable< Key, Value, Hash, KeyEqual >::size() const noexcept
  {
    return size_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::insert(const ValueType& value)
  {
    size_t home_index = hasher(value.first) % capacity_;
    if (array_[home_index].first == NodeType::Empty)
    {
      array_[home_index].first = NodeType::Fill;
      array_[home_index].second = Node{value, 0};
      return Iterator(array_ + home_index, array_ + capacity_);
    }
    std::pair< bool, T > prob_res = robRich(value, home_index);
    if (!prob_res.first)
    {}
    if (prob_res.second.first == NodeType::Fill)
    {
      return insert(prob_res.second.second.data);
    }
    return Iterator(&prob_res.second, array_ + capacity_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::find(const Key& key)
  {
    ConstIterator it = static_cast< const HashTable& >(*this).find(key);
    return Iterator(it.node_, it.end_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::find(const Key& key) const
  {
    auto it = begin();
    for (; it != end(); it++)
    {
      if (it->first == key)
      {
        return it;
      }
    }
    return it;
  }



  template< class Key, class Value, class Hash, class KeyEqual >
  float HashTable< Key, Value, Hash, KeyEqual >::load_factor() const noexcept
  {
    return (size_ * 1.0) / (capacity_ * 1.0);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  float HashTable< Key, Value, Hash, KeyEqual >::max_load_factor() const noexcept
  {
    return max_load_factor_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::max_load_factor(float mlf) noexcept
  {
    max_load_factor_ = mlf;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::clear() noexcept
  {
    for (size_t i = 0; i < capacity_; i++)
    {
      array_[i].first = NodeType::Empty;
    }
    size_ = 0;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::swap(HashTable& other)
  {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
    std::swap(hasher, other.hasher);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  std::pair< bool, typename HashTable< Key, Value, Hash, KeyEqual >::T >
    HashTable< Key, Value, Hash, KeyEqual >::robRich(const ValueType& value, size_t home_slot)
  {
    std::pair< NodeType, Node > node{NodeType::Fill, Node{value, 1}};
    for (size_t i = (home_slot + 1) % capacity_; i != home_slot; i = (i + 1) % capacity_)
    {
      if (node.second.psl > array_[i].second.psl)
      {
        node.swap(array_[i]);
        return {true, node};
      }
      node.second.psl++;
    }
    return {false, node};
  }
}

#endif

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <functional>
#include <cmath>
#include <cassert>
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
    HashTable(std::initializer_list< ValueType > il);
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
    template< class InputIterator >
    void insert(InputIterator first, InputIterator last);
    Iterator insert(ConstIterator hint, const ValueType& value);

    template< class... Args >
    Iterator emplace(Args&&... args);
    template< class... Args >
    Iterator emplace_hint(ConstIterator hint, Args&&... args);

    size_t erase(const Key& key);
    Iterator erase(Iterator pos);
    Iterator erase(ConstIterator pos);
    Iterator erase(ConstIterator first, ConstIterator last);

    Value& at(const Key& key);
    const Value& at(const Key& key) const;
    Iterator find(const Key& key);
    ConstIterator find(const Key& key) const;

    void clear() noexcept;
    void swap(HashTable& other);

    float load_factor() const noexcept;
    float max_load_factor() const noexcept;
    void max_load_factor(float mlf) noexcept;
    void rehash();
  private:
    float max_load_factor_ = 0.7;
    size_t size_;
    size_t capacity_;
    T* array_;
    Hash hasher;

    size_t get_home_index(const Key& key) const;
    std::pair< size_t, T > rob_rich(size_t home_index, const Node& value);
    Iterator insert_node(size_t index, const Node& node);
    size_t get_next_prime_capacity();
  };

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable():
    size_(0),
    capacity_(11),
    array_(new T[capacity_]),
    hasher()
  {
    clear();
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(const HashTable& other):
    size_(0),
    capacity_(other.capacity_),
    array_(new T[capacity_]),
    hasher(other.hasher)
  {
    clear();
    for (size_t i = 0; i != other.capacity_; i++)
    {
      if (other.array_[i].first == NodeType::Fill)
      {
        array_[i] = other.array_[i];
      }
    }
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(HashTable&& other) noexcept:
    size_(std::exchange(other.size_, 0)),
    capacity_(std::exchange(other.capacity_, 0)),
    array_(std::exchange(other.array_, nullptr)),
    hasher(other.hasher)
  {}

  template< class Key, class Value, class Hash, class KeyEqual >
  template< class InputIterator >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(InputIterator first, InputIterator last):
    HashTable()
  {
    insert(first, last);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(std::initializer_list< ValueType > il):
    HashTable(il.begin(), il.end())
  {}


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
    return emplace(value);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::insert(ValueType&& value)
  {
    return emplace(std::forward< ValueType >(value));
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  template< class InputIterator >
  void HashTable< Key, Value, Hash, KeyEqual >::insert(InputIterator first, InputIterator last)
  {
    for (; first != last; first++)
    {
      emplace(*first);
    }
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual >
    HashTable< Key, Value, Hash, KeyEqual >::insert(ConstIterator hint, const ValueType& value)
  {
    return emplace_hint(hint, std::forward< ValueType >(value));
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  template< class... Args >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::emplace(Args&&... args)
  {
    if (size_ > max_load_factor_ * capacity_)
    {
      rehash();
    }
    ValueType value(std::forward< Args >(args)...);
    size_t home_index = get_home_index(value.first);
    ConstIterator hint(array_ + home_index, array_ + capacity_);
    return emplace_hint(hint, std::move(value));
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  template< class... Args >
  HashIterator< Key, Value, Hash, KeyEqual >
    HashTable< Key, Value, Hash, KeyEqual >::emplace_hint(ConstIterator hint, Args&&... args)
  {
    if (size_ > max_load_factor_ * capacity_)
    {
      rehash();
    }
    ValueType value(std::forward< Args >(args)...);
    size_t home_index = hint.node_ - array_;
    if (hint == end())
    {
      home_index = get_home_index(value.first);
    }
    Node node{value, 0};
    size_++;
    return insert_node(home_index, node);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  size_t HashTable< Key, Value, Hash, KeyEqual >::erase(const Key& key)
  {
    size_t size_old = size_;
    while (find(key) != end())
    {
      erase(find(key));
    }
    return size_old - size_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::erase(Iterator pos)
  {
    assert(pos != end() && "You try to delete beyond table's bound");

    pos.node_->first = NodeType::Empty;
    size_t deleted_index = pos.node_ - array_;
    size_t i = (deleted_index + 1) % capacity_;
    while (array_[i].first != NodeType::Empty)
    {
      if (array_[i].second.psl == 0)
      {
        break;
      }
      size_t prev = i - 1;
      if (i == 0)
      {
        prev = capacity_ - 1;
      }
      std::swap(array_[i], array_[prev]);
      i = (i + 1) % capacity_;
    }
    if (pos.node_->first == NodeType::Empty)
    {
      ++pos;
    }
    return pos;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::erase(ConstIterator pos)
  {
    Iterator it(pos.node_, pos.end_);
    return erase(it);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual >
    HashTable< Key, Value, Hash, KeyEqual >::erase(ConstIterator first, ConstIterator last)
  {
    while (first != last)
    {
      first = erase(first);
    }
    Iterator it(first.node_, first.end_);
    return it;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  Value& HashTable< Key, Value, Hash, KeyEqual >::at(const Key& key)
  {
    return const_cast< Value& >(static_cast< const HashTable& >(*this).at(key));
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  const Value& HashTable< Key, Value, Hash, KeyEqual >::at(const Key& key) const
  {
    auto it = find(key);
    if (it == end())
    {
      throw std::out_of_range("Container does not have an element with the such key");
    }
    return it->second;
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
    /*size_t psl = 0;
    size_t home_index = get_home_index(key);
    Iterator it(array_ + home_index, array_ + capacity_);
    for (; it != end(); it++)
    {
      if (it.node_->first == NodeType::Empty)
      {
        break;
      }
      if (it.node_->second.psl < psl)
      {
        break;
      }
      if (it->first == key)
      {
        return it;
      }
      psl++;
    }*/
    for (auto it = begin(); it != end(); it++)
    {
      if (it->first == key)
      {
        return it;
      }
    }
    return end();
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
    if (size_ > capacity_ * max_load_factor_)
    {
      rehash();
    }
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  void HashTable< Key, Value, Hash, KeyEqual >::rehash()
  {
    capacity_ = get_next_prime_capacity();
    T* array_new = new T[capacity_];
    std::swap(array_new, array_);
    clear();
    for (size_t i = 0; i < capacity_; i++)
    {
      if (array_new[i].first == NodeType::Fill)
      {
        insert(array_new[i].second.data);
      }
    }
    delete[] array_new;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  size_t HashTable< Key, Value, Hash, KeyEqual >::get_home_index(const Key& key) const
  {
    return hasher(key) % capacity_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  std::pair< size_t, typename HashTable< Key, Value, Hash, KeyEqual >::T >
    HashTable< Key, Value, Hash, KeyEqual >::rob_rich(size_t home_index, const Node& node)
  {
    std::pair< NodeType, Node > node_t{NodeType::Fill, node};
    node_t.second.psl = 1;
    for (size_t i = (home_index + 1) % capacity_; i != home_index; i = (i + 1) % capacity_)
    {
      if (node_t.first == NodeType::Empty)
      {
        node_t.swap(array_[i]);
        return {i, node_t};
      }
      if (node_t.second.psl > array_[i].second.psl)
      {
        node_t.swap(array_[i]);
        return {i, node_t};
      }
      node_t.second.psl++;
    }
    return {home_index, node_t};
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual >
    HashTable< Key, Value, Hash, KeyEqual >::insert_node(size_t index, const Node& node)
  {
    size_t home_index;
    if (index < node.psl)
    {
      home_index = capacity_ - node.psl;
    }
    else
    {
      home_index = index - node.psl;
    }
    if (array_[home_index].first == NodeType::Empty)
    {
      array_[home_index].first = NodeType::Fill;
      array_[home_index].second = node;
      return Iterator(array_ + home_index, array_ + capacity_);
    }
    std::pair< size_t, T > rob_res = rob_rich(home_index, node);
    if (rob_res.first == home_index)
    {
      rehash();
    }
    if (rob_res.second.first == NodeType::Fill)
    {
      return insert_node(rob_res.first, rob_res.second.second);
    }
    return Iterator(array_ + rob_res.first, array_ + capacity_);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  size_t HashTable< Key, Value, Hash, KeyEqual >::get_next_prime_capacity()
  {
    size_t new_cap = capacity_ * 2;

    for (size_t i = new_cap + 1; i < std::pow(10, 7); i += 2)
    {
      bool prime = true;
      for (size_t del = 3; del < std::round(std::sqrt(new_cap)) + 1; del++)
      {
        if (i % del == 0)
        {
          prime = false;
          break;
        }
      }
      if (prime)
      {
        return i;
      }
    }
    return new_cap;
  }
}

#endif

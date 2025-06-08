#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
#include <functional>
#include <cmath>
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

    template< class... Args >
    Iterator emplace(Args&&... args);
    template< class... Args >
    Iterator emplace_hint(ConstIterator hint, Args&&... args);

    size_t erase(const Key& key);
    Iterator erase(Iterator pos);
    Iterator erase(ConstIterator pos);

    Iterator find(const Key& key);
    ConstIterator find(const Key& key) const;

    void clear() noexcept;
    void swap(HashTable& other);

    float load_factor() const noexcept;
    float max_load_factor() const noexcept;
    void max_load_factor(float mlf) noexcept; //resixe if new mlf
    void rehash();
  private:
    float max_load_factor_ = 0.7;
    size_t size_;
    size_t capacity_;
    T* array_;
    Hash hasher;

    std::pair< size_t, T > rob_rich(size_t home_index, const Node& value);
    Iterator insert_node(size_t index, const Node& node);
    size_t get_next_prime_capacity();
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
  HashTable< Key, Value, Hash, KeyEqual >::HashTable(const HashTable& other):
    size_(other.size_),
    capacity_(other.capacity_),
    array_(new T[capacity_]()),
    hasher(other.hasher)
  {
    for (auto it = other.begin(); it < other.end(); it++)
    {
      array_.emplace(*it);
    }
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
    emplace(value);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::insert(ValueType&& value)
  {
    emplace(std::forward< ValueType >(value));
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
    size_t home_index = hasher(value.first) % capacity_;
    ConstIterator hint(array_ + home_index, array_ + capacity_);
    return emplace_hint(hint, std::move(value));
    /*ValueType value(std::forward< Args >(args)...);
    size_t home_index = hasher(value.first) % capacity_;
    Node node{value, 0};
    size_++;
    return insert_node(home_index, node);*/
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
    size_t home_index = hint.node_ - array_;;
    Node node{value, 0};
    size_++;
    return insert_node(home_index, node);
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
    T* array_new = new T[get_next_prime_capacity()]();
    std::swap(array_new, array_);
    clear();
    for (size_t i = 0; i < capacity_; i++)
    {
      if (array_new[i].first == NodeType::Fill)
      {
        insert(array_new[i].second.data);
      }
    }
    capacity_ = get_next_prime_capacity();
    delete[] array_new;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  std::pair< size_t, typename HashTable< Key, Value, Hash, KeyEqual >::T >
    HashTable< Key, Value, Hash, KeyEqual >::rob_rich(size_t home_index, const Node& node)
  {
    std::pair< NodeType, Node > node_t{NodeType::Fill, node};
    node_t.second.psl = 1;
    for (size_t i = (home_index + 1) % capacity_; i != home_index; i = (i + 1) % capacity_)
    {
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
  HashIterator< Key, Value, Hash, KeyEqual > HashTable< Key, Value, Hash, KeyEqual >::insert_node(size_t index, const Node& node)
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
    {}
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

#ifndef HASH_ITERATORS_HPP
#define HASH_ITERATORS_HPP
#include <iterator>
#include "hash-node.hpp"

namespace alymova
{
  template< class Key, class Value, class Hash, class KeyEqual >
  class HashTable;

  template< class Key, class Value, class Hash = std::hash< Key >, class KeyEqual = std::equal_to< Key > >
  struct HashConstIterator:
    public std::iterator< std::forward_iterator_tag, std::pair< Key, Value > >
  {
    using Node = detail::HashNode< Key, Value >;

    HashConstIterator() = default;
    HashConstIterator& operator++() noexcept;
    HashConstIterator operator++(int) noexcept;
    bool operator==(const HashConstIterator& other) const noexcept;
    bool operator!=(const HashConstIterator& other) const noexcept;
    const std::pair< Key, Value >& operator*() const noexcept;
    const std::pair< Key, Value >& operator->() const noexcept;
  private:
    Node* node_;

    HashConstIterator(Node* node) noexcept;

    friend class HashTable< Key, Value, Hash, KeyEqual >;
  };

  template< class Key, class Value, class Hash = std::hash< Key >, class KeyEqual = std::equal_to< Key > >
  struct HashIterator:
    public std::iterator< std::forward_iterator_tag, std::pair< Key, Value > >
  {
    using Node = detail::HashNode< Key, Value >;

    HashIterator() = default;
    HashIterator& operator++() noexcept;
    HashIterator operator++(int) noexcept;
    bool operator==(const HashIterator& other) const noexcept;
    bool operator!=(const HashIterator& other) const noexcept;
    std::pair< Key, Value >& operator*() noexcept;
    std::pair< Key, Value >& operator->() noexcept;
  private:
    Node* node_;

    HashIterator(Node* node) noexcept;

    friend class HashTable< Key, Value, Hash, KeyEqual >;
  };

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual >::HashConstIterator(Node* node) noexcept:
    node_(node)
  {}

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual >&
    HashConstIterator< Key, Value, Hash, KeyEqual >::operator++() noexcept
  {
    node_++;
    while (node_->isEmpty)
    {
      node_++;
    }
    return *this;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashConstIterator< Key, Value, Hash, KeyEqual >
    HashConstIterator< Key, Value, Hash, KeyEqual >::operator++(int) noexcept
  {
    HashConstIterator old = *this;
    ++(*this);
    return old;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  bool HashConstIterator< Key, Value, Hash, KeyEqual >::operator==(const HashConstIterator& other) const noexcept
  {
    return node_ == other.node_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  bool HashConstIterator< Key, Value, Hash, KeyEqual >::operator!=(const HashConstIterator& other) const noexcept
  {
    return !(*this == other);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  const std::pair< Key, Value >&
    HashConstIterator< Key, Value, Hash, KeyEqual>::operator*() const noexcept
  {
    assert(node_->isEmpty && "You try to dereference empty node");

    return node_->data;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  const std::pair< Key, Value >&
    HashConstIterator< Key, Value, Hash, KeyEqual >::operator->() const noexcept
  {
    assert(node_->isEmpty && "You try to dereference empty node");

    return std::addressof(node_->data);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual >::HashIterator(Node* node) noexcept:
    node_(node)
  {}

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual >&
    HashIterator< Key, Value, Hash, KeyEqual >::operator++() noexcept
  {
    node_++;
    while (node_->isEmpty)
    {
      node_++;
    }
    return *this;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  HashIterator< Key, Value, Hash, KeyEqual >
    HashIterator< Key, Value, Hash, KeyEqual >::operator++(int) noexcept
  {
    HashIterator old = *this;
    ++(*this);
    return old;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  bool HashIterator< Key, Value, Hash, KeyEqual >::operator==(const HashIterator& other) const noexcept
  {
    return node_ == other.node_;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  bool HashIterator< Key, Value, Hash, KeyEqual >::operator!=(const HashIterator& other) const noexcept
  {
    return !(*this == other);
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  std::pair< Key, Value >&
    HashIterator< Key, Value, Hash, KeyEqual>::operator*() noexcept
  {
    assert(node_->isEmpty && "You try to dereference empty node");

    return node_->data;
  }

  template< class Key, class Value, class Hash, class KeyEqual >
  std::pair< Key, Value >&
    HashIterator< Key, Value, Hash, KeyEqual >::operator->() noexcept
  {
    assert(node_->isEmpty && "You try to dereference empty node");

    return std::addressof(node_->data);
  }
}

#endif

#ifndef HASH_TABLE_ITERATOR_HPP
#define HASH_TABLE_ITERATOR_HPP

#include <type_traits>
#include <iterator>

namespace detail {
  enum class HashTableIteratorType
  {
    CONSTANT,
    NONCONSTANT,
  };
}

namespace maslevtsov {
  template< class T, detail::HashTableIteratorType it_type >
  class HashTableIterator final: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    using reference_type = std::conditional< it_type == detail::HashTableIteratorType::CONSTANT, const T&, T& >::type;
    using pointer_type = std::conditional< it_type == detail::HashTableIteratorType::CONSTANT, const T*, T* >::type;

    HashTableIterator();

    HashTableIterator& operator++();
    HashTableIterator& operator++(int);

    reference_type operator*() const;
    pointer_type operator->() const;

    bool operator==(const HashTableIterator& rhs) const;
    bool operator!=(const HashTableIterator& rhs) const;

  private:
    template< class Key, class Type, class Hash, class KeyEqual >
    friend class HashTable;

    using hash_table_t = std::conditional< it_type == detail::HashTableIteratorType::CONSTANT,
      const HashTable< Key, Type, Hash, KeyEqual >, HashTable< Key, Type, Hash, KeyEqual > >::type;

    hash_table_t* table_;
    size_t index_;

    explicit HashTableIterator(hash_table_t* table, size_t index_);
  };
}

#endif

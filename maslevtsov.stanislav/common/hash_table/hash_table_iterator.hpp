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
  template< class Key, class T, class Hash, class KeyEqual >
  class HashTable;

  template< class Key, class T, class Hash, class KeyEqual, detail::HashTableIteratorType it_type >
  class HashTableIterator final: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    using value_type = std::pair< Key, T >;
    using reference_type = typename std::conditional< it_type == detail::HashTableIteratorType::CONSTANT,
      const value_type&, value_type& >::type;
    using pointer_type = typename std::conditional< it_type == detail::HashTableIteratorType::CONSTANT,
      const value_type*, value_type* >::type;

    HashTableIterator();

    HashTableIterator& operator++();
    HashTableIterator& operator++(int);

    reference_type operator*() const;
    pointer_type operator->() const;

    bool operator==(const HashTableIterator& rhs) const;
    bool operator!=(const HashTableIterator& rhs) const;

  private:
    friend class HashTable< Key, T, Hash, KeyEqual >;

    using hash_table_t = typename std::conditional< it_type == detail::HashTableIteratorType::CONSTANT,
      const HashTable< Key, T, Hash, KeyEqual >, HashTable< Key, T, Hash, KeyEqual > >::type;

    hash_table_t* table_;
    size_t index_;

    HashTableIterator(hash_table_t* table, size_t index_);
  };
}

#endif

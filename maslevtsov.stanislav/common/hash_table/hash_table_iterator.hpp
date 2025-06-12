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
    HashTableIterator();

    HashTableIterator& operator++();
    HashTableIterator& operator++(int);

    typename std::conditional< it_type == detail::HashTableIteratorType::CONSTANT, const T&, T& >::type
      operator*() const;
    typename std::conditional< it_type == detail::HashTableIteratorType::CONSTANT, const T*, T* >::type
      operator->() const;

    bool operator==(const HashTableIterator& rhs) const;
    bool operator!=(const HashTableIterator& rhs) const;

  private:
    template< class Key, class Type, class Hash, class KeyEqual >
    friend class HashTable;

    T* ptr_;

    explicit HashTableIterator(T* ptr);
  };
}

#endif

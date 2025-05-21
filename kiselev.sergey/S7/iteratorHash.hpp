#ifndef ITERATORHASH_HPP
#define ITERATORHASH_HPP
#include <cstddef>
#include <utility>
namespace kiselev
{
  template< class Key, class Value, class Hash1, class Hash2, class Equal >
  class HashTable;

  template< class Key, class Value, class Hash1, class Hash2, class Equal, bool IsConst >
  class IteratorHash
  {
  public:
    using value = std::pair< Key, Value >;
    using reference = std::conditional_t< IsConst, const value&, value& >;
    using pointer = std::conditional_t< IsConst, const value*, value* >;
    using iterator = IteratorHash< Key, Value, Hash1, Hash2, Equal, IsConst >;
    using table = HashTable< Key, Value, Hash1, Hash2, Equal >;

    IteratorHash();
    template < bool OtherIsConst, std::enable_if_t< IsConst && !OtherIsConst, int > = 0 >
    IteratorHash(const IteratorHash< Key, Value, Hash1, Hash2, Equal, OtherIsConst >&) noexcept;
    template< bool OtherIsConst, std::enable_if_t< IsConst && !OtherIsConst, int > = 0 >
    iterator& operator=(const IteratorHash< Key, Value, Hash1, Hash2, Equal, OtherIsConst >&) noexcept;

    iterator& operator++() noexcept;
    iterator operator++(int) noexcept;

    iterator& operator--() noexcept;
    iterator operator--(int) noexcept;

    reference operator*() const noexcept;
    pointer operator->() const noexcept;

    bool operator==(const iterator&) const noexcept;
    bool operator!=(const iterator&) const noexcept;
  private:
    table* table_;
    size_t index_;
    friend class IteratorHash< Key, Value, Hash1, Hash2, Equal, !IsConst >;
    friend class HashTable< Key, Value, Hash1, Hash2, Equal >;
  };
}
#endif

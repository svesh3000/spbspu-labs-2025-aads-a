#ifndef UNORDERED_BASE_CONSTRUCT_DESTRUCT_HPP
#define UNORDERED_BASE_CONSTRUCT_DESTRUCT_HPP

#include "declaration.hpp"

#include <utility>

template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::UnorderedBase()
    noexcept(noexcept_default):
  capacity_(0),
  size_(0),
  max_factor_(default_max_factor),
  data_(nullptr),
  raw_(nullptr),
  cached_begin_(nullptr),
  cached_rbegin_(nullptr)
{}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::UnorderedBase(size_type cnt, hasher hash, key_equal eq):
  capacity_(0),
  size_(0),
  max_factor_(default_max_factor),
  data_(nullptr),
  raw_(nullptr),
  cached_begin_(nullptr),
  cached_rbegin_(nullptr),
  hash_(std::move(hash)),
  equal_(std::move(eq))
{
  allocate(cnt);
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::UnorderedBase(UnorderedBase&& rhs) noexcept(noexcept_move):
  capacity_(std::exchange(rhs.capacity_, 0)),
  size_(std::exchange(rhs.size_, 0)),
  max_factor_(std::exchange(rhs.max_factor_, default_max_factor)),
  data_(std::exchange(rhs.data_, nullptr)),
  raw_(std::exchange(rhs.raw_, nullptr)),
  cached_begin_(std::exchange(rhs.cached_begin_, nullptr)),
  cached_rbegin_(std::exchange(rhs.cached_rbegin_, nullptr)),
  hash_(std::move(rhs.hash_)),
  equal_(std::move(rhs.equal_))
{}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::UnorderedBase(const UnorderedBase& rhs):
  UnorderedBase(rhs.capacity_, rhs.hash_, rhs.equal_)
{
  insert(begin(), end());
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::UnorderedBase
    (std::initializer_list< value_type > init, hasher hash, key_equal eq):
  UnorderedBase(0, std::move(hash), std::move(eq))
{
  reserve(init.size());
  insert(init.begin(), init.end());
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
template< class InputIt >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::UnorderedBase(InputIt from, InputIt to,
      hasher hash, key_equal eq):
  UnorderedBase(0, std::move(hash), std::move(eq))
{
  for (; from != to; ++from)
  {
    insert(*from);
  }
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >&
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::operator=(const UnorderedBase& rhs)
{
  UnorderedBase temp = rhs;
  swap(temp);
  return *this;
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >&
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::operator=(UnorderedBase&& rhs)
    noexcept(noexcept(swap(std::declval< UnorderedBase& >())))
{
  UnorderedBase temp = std::move(rhs);
  swap(temp);
  return *this;
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >&
    rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::operator=(std::initializer_list< value_type > init)
{
  UnorderedBase temp = init;
  swap(temp);
  return *this;
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::~UnorderedBase()
{
  clear();
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
void rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::swap(UnorderedBase& rhs)
    noexcept(is_nothrow_swappable_v< hasher > && is_nothrow_swappable_v< key_equal >)
{
  static_assert(!is_nothrow_swappable_v< hasher > && !is_nothrow_swappable_v< key_equal >, "");
  std::swap(hash_, rhs.hash_);
  std::swap(equal_, rhs.equal_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(size_, rhs.size_);
  std::swap(max_factor_, rhs.max_factor_);
  std::swap(data_, rhs.data_);
  std::swap(raw_, rhs.raw_);
  std::swap(cached_begin_, rhs.cached_begin_);
  std::swap(cached_rbegin_, rhs.cached_rbegin_);
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
void rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::clear() noexcept
{
  erase(begin(), end());
}
template< class K, class T, class H, class E, bool IsSet, bool IsMulti >
void rychkov::UnorderedBase< K, T, H, E, IsSet, IsMulti >::allocate(size_type new_capacity)
{
  if (new_capacity == 0)
  {
    raw_ = nullptr;
    data_ = nullptr;
    capacity_ = 0;
    return;
  }
  raw_ = new unsigned char[new_capacity * sizeof(stored_value) + alignof(stored_value) - 1];
  data_ = reinterpret_cast< stored_value* >(reinterpret_cast< size_t >(raw_ + alignof(stored_value) - 1)
        & ~(alignof(stored_value) - 1));
  capacity_ = new_capacity;
}

#endif

#ifndef ACCESS_HPP
#define ACCESS_HPP

#include "declaration.hpp"

#include <exception>

class rychkov::bad_variant_access: public std::exception
{};

template< class T, class... Types >
T* rychkov::get_if(Variant< Types... >* variant) noexcept
{
  if (variant->active_ == find_uniq_type_in_pack< T, Types... >())
  {
    return reinterpret_cast< T* >(variant->data_);
  }
  return nullptr;
}
template< class T, class... Types >
const T* rychkov::get_if(const Variant< Types... >* variant) noexcept
{
  if (variant->active_ == find_uniq_type_in_pack< T, Types... >())
  {
    return reinterpret_cast< const T* >(variant->data_);
  }
  return nullptr;
}
template< size_t N, class... Types >
rychkov::variant_alternative_t< N, Types... >* rychkov::get_if(Variant< Types... >* variant) noexcept
{
  if (variant->active_ == N)
  {
    return reinterpret_cast< variant_alternative_t< N, Types... >* >(variant->data_);
  }
  return nullptr;
}
template< size_t N, class... Types >
const rychkov::variant_alternative_t< N, Types... >* rychkov::get_if(const Variant< Types... >* variant) noexcept
{
  if (variant->active_ == N)
  {
    return reinterpret_cast< const variant_alternative_t< N, Types... >* >(variant->data_);
  }
  return nullptr;
}

template< class T, class... Types >
T& rychkov::get(Variant< Types... >& variant)
{
  T* resultPtr = get_if< T >(&variant);
  if (resultPtr != nullptr)
  {
    return *resultPtr;
  }
  throw bad_variant_access();
}
template< class T, class... Types >
const T& rychkov::get(const Variant< Types... >& variant)
{
  T* resultPtr = get_if< T >(&variant);
  if (resultPtr != nullptr)
  {
    return *resultPtr;
  }
  throw bad_variant_access();
}
template< class T, class... Types >
T&& rychkov::get(Variant< Types... >&& variant)
{
  return std::move(get< T >(variant));
}
template< class T, class... Types >
const T&& rychkov::get(const Variant< Types... >&& variant)
{
  return std::move(get< T >(variant));
}
template< size_t N, class... Types >
rychkov::variant_alternative_t< N, Types... >& rychkov::get(Variant< Types... >& variant)
{
  rychkov::variant_alternative_t< N, Types... >* resultPtr = get_if< N, Types... >(&variant);
  if (resultPtr != nullptr)
  {
    return *resultPtr;
  }
  throw bad_variant_access();
}
template< size_t N, class... Types >
const rychkov::variant_alternative_t< N, Types... >& rychkov::get(const Variant< Types... >& variant)
{
  rychkov::variant_alternative_t< N, Types... >* resultPtr = get_if< N >(&variant);
  if (resultPtr != nullptr)
  {
    return *resultPtr;
  }
  throw bad_variant_access();
}
template< size_t N, class... Types >
rychkov::variant_alternative_t< N, Types... >&& rychkov::get(Variant< Types... >&& variant)
{
  return std::move(get< N >(variant));
}
template< size_t N, class... Types >
const rychkov::variant_alternative_t< N, Types... >&& rychkov::get(const Variant< Types... >&& variant)
{
  return std::move(get< N >(variant));
}

template< class... Types >
size_t rychkov::Variant< Types... >::index() const noexcept
{
  return active_;
}
template< class... Types >
bool rychkov::Variant< Types... >::valueless_by_exception() const noexcept
{
  return active_ == -1U;
}

template< class T, class... Types >
bool rychkov::holds_alternative(const Variant< Types... >& variant) noexcept
{
  return variant.index() == find_uniq_type_in_pack< T, Types... >();
}

#endif

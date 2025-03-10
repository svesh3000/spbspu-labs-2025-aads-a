#ifndef CONSTRUCT_DESTRUCT_HPP
#define CONSTRUCT_DESTRUCT_HPP

#include "declaration.hpp"

template< class... Types >
template< class T0 >
rychkov::Variant< Types... >::Variant() noexcept(std::is_nothrow_default_constructible< T0 >::value):
  active_(0)
{
  new (&data_) T0();
}
template< class... Types >
rychkov::Variant< Types... >::Variant(const Variant& rhs):
  active_(rhs.active_)
{
  static_assert(conjunction_v< std::is_copy_constructible< Types >::value... >);
  copy(rhs);
}
template< class... Types >
rychkov::Variant< Types... >::Variant(Variant&& rhs) noexcept(is_nothrow_move_constructible_v):
  active_(rhs.active_)
{
  static_assert(conjunction_v< std::is_move_constructible< Types >::value... >);
  move(std::move(rhs));
}
template< class... Types >
template< class T >
rychkov::Variant< Types... >::Variant(T&& value):
  active_(find_uniq_type_in_pack< remove_cvref_t< T >, Types... >())
{
  using real_type = remove_cvref_t< T >;
  new (data_) real_type(std::forward< T >(value));
}
template< class... Types >
template< class T, class... Args >
rychkov::Variant< Types... >::Variant(in_place_type_t< T >, Args&&... args):
  active_(find_uniq_type_in_pack< T, Types... >())
{
  new (data_) T(std::forward< Args >(args)...);
}
template< class... Types >
template< size_t N, class... Args >
rychkov::Variant< Types... >::Variant(in_place_index_t< N >, Args&&... args):
  active_(N)
{
  using real_type = variant_alternative_t< N, Types... >;
  new (data_) real_type(std::forward< Args >(args)...);
}
template< class... Types >
rychkov::Variant< Types... >::~Variant()
{
  destruct();
}

template< class... Types >
rychkov::Variant< Types... >& rychkov::Variant< Types... >::operator=(const Variant& rhs)
{
  static_assert(conjunction_v< std::is_copy_constructible< Types >::value... >);
  destruct();
  copy(rhs);
  active_ = rhs.active_;
  return *this;
}
template< class... Types >
rychkov::Variant< Types... >& rychkov::Variant< Types... >::operator=(Variant&& rhs) noexcept(is_nothrow_move_constructible_v)
{
  static_assert(conjunction_v< std::is_move_constructible< Types >::value... >);
  destruct();
  move(std::move(rhs));
  active_ = rhs.active_;
  return *this;
}

#endif

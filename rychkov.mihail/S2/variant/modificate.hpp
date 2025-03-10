#ifndef MODIFICATE_HPP
#define MODIFICATE_HPP

#include "declaration.hpp"

template< class... Types >
void rychkov::Variant< Types... >::copy(const Variant& rhs)
{
  static constexpr details::copier_t copiers[sizeof...(Types)] = {details::copy_function< Types >...};
  if (rhs.active_ != -1U)
  {
    copiers[rhs.active_](data_, rhs.data_);
  }
}
template< class... Types >
void rychkov::Variant< Types... >::move(Variant&& rhs) noexcept(is_nothrow_move_constructible_v)
{
  constexpr bool Nothrow = is_nothrow_move_constructible_v;
  using mover_ptr = details::mover_t< Nothrow >;

  static constexpr mover_ptr movers[sizeof...(Types)] = {details::move_function< Types, Nothrow >...};
  if (rhs.active_ != -1U)
  {
    movers[rhs.active_](data_, rhs.data_);
  }
}
template< class... Types >
void rychkov::Variant< Types... >::destruct()
{
  static constexpr details::destructor_t destructors[sizeof...(Types)] = {details::destructor_function< Types >...};
  if (active_ != -1U)
  {
    destructors[active_](data_);
  }
}

template< class... Types >
template< class T, class... Args >
T& rychkov::Variant< Types... >::emplace(Args&&... args)
{
  using real_type = remove_cvref_t< T >;
  destruct();
  new (data_) real_type(std::forward< Args >(args)...);
  active_ = find_uniq_type_in_pack< remove_cvref_t< T >, Types... >();
}
template< class... Types >
template< size_t N, class... Args >
rychkov::variant_alternative_t< N, Types... >& rychkov::Variant< Types... >::emplace(Args&&... args)
{
  using real_type = variant_alternative_t< N, Types... >;
  destruct();
  new (data_) real_type(std::forward< Args >(args)...);
  active_ = N;
}

#endif

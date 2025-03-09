#ifndef VARIANT_HPP
#define VARIANT_HPP

#include <algorithm>
#include "variant_tools.hpp"

namespace rychkov
{
  template< class... Types >
  class Variant
  {
  public:
    template< class T0 = variant_alternative_t< 0, Types... > >
    Variant() noexcept(std::is_nothrow_default_constructible< T0 >::value):
      active_(0)
    {
      new (&data_) T0();
    }

    Variant(const Variant& rhs):
      active_(rhs.active_)
    {
      static_assert(conjunction_v< std::is_copy_constructible< Types >::value... >);
      copy<>(rhs);
    }

    Variant(Variant&& rhs) noexcept(is_nothrow_move_constructible_v):
      active_(rhs.active_)
    {
      static_assert(conjunction_v< std::is_move_constructible< Types >::value... >);
      move<>(std::move(rhs));
    }
    template< class T >
    Variant(T&& value):
      active_(find_uniq_type_in_pack< remove_cvref_t< T >, Types... >())
    {
      using real_type = remove_cvref_t< T >;
      new (data_) real_type(std::forward< T >(value));
    }
    template< class T, class... Args >
    Variant(in_place_type_t< T >, Args&&... args):
      active_(find_uniq_type_in_pack< T, Types... >())
    {
      new (data_) T(std::forward< Args >(args)...);
    }
    template< size_t N, class... Args >
    Variant(in_place_index_t< N >, Args&&... args):
      active_(N)
    {
      using real_type = variant_alternative_t< N, Types... >;
      new (data_) real_type(std::forward< Args >(args)...);
    }

    Variant& operator=(const Variant& rhs)
    {
      static_assert(conjunction_v< std::is_copy_constructible< Types >::value... >);
      destruct();
      copy<>(rhs);
      active_ = rhs.active_;
      return *this;
    }
    Variant& operator=(Variant&& rhs) noexcept(is_nothrow_move_constructible_v)
    {
      static_assert(conjunction_v< std::is_move_constructible< Types >::value... >);
      destruct();
      move<>(std::move(rhs));
      active_ = rhs.active_;
      return *this;
    }
    ~Variant()
    {
      destruct();
    }
  private:
    using size_type = size_t;

    static constexpr bool is_nothrow_move_constructible_v = conjunction_v< std::is_trivially_move_constructible< Types >::value... >;
    static constexpr size_t size_ = std::max({sizeof(Types)...});

    size_type active_;
    byte data_[size_];

    template< class = void >
    void copy(const Variant& rhs)
    {
      static details::copier_t copiers[sizeof...(Types)] = {details::copy_function< Types >...};
      if (rhs.active_ != -1U)
      {
        copiers[rhs.active_](data_, rhs.data_);
      }
    }
    template< class = void >
    void move(Variant&& rhs) noexcept(is_nothrow_move_constructible_v)
    {
      static details::mover_t movers[sizeof...(Types)] = {details::move_function< Types >...};
      if (rhs.active_ != -1U)
      {
        movers[rhs.active_](data_, rhs.data_);
      }
    }
    void destruct()
    {
      static details::destructor_t destructors[sizeof...(Types)] = {details::destructor_function< Types >...};
      if (active_ != -1U)
      {
        destructors[active_](data_);
      }
    }
  };
}

#endif

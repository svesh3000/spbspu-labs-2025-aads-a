#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <type_traits.hpp>

namespace rychkov
{
  using byte = unsigned char;

  template< size_t N, class T, class... Types >
  struct variant_alternative
  {
    using type = typename variant_alternative< N - 1, Types... >::type;
  };
  template< class T, class... Types >
  struct variant_alternative< 0, T, Types... >
  {
    using type = T;
  };
  template< size_t N, class... Types >
  using variant_alternative_t = typename variant_alternative< N, Types... >::type;

  template< class... Types >
  constexpr size_t variant_size_v = sizeof...(Types);

  namespace details
  {
    template< class U, class T >
    constexpr size_t find_unique()
    {
      return !std::is_same< U, T >::value;
    }
    template< class U, class T1, class T2, class... Types >
    constexpr size_t find_unique()
    {
      constexpr bool found = std::is_same< U, T1 >::value;
      constexpr size_t resultAfterThis = find_unique< U, T2, Types... >();
      static_assert(!found || (resultAfterThis == 1 + sizeof...(Types)));
      return found ? 0 : 1 + resultAfterThis;
    }
  }
  template< class U, class... Types >
  constexpr size_t find_uniq_type_in_pack()
  {
    constexpr size_t result = details::find_unique< U, Types... >();
    static_assert(result != sizeof...(Types));
    return result;
  }
  template< class T, class... Types >
  constexpr bool exactly_once = find_uniq_type_in_pack< T, Types... >() < sizeof...(Types);

  template< class T >
  struct in_place_type_t
  {};
  template< size_t N >
  struct in_place_index_t
  {};
  constexpr size_t variant_npos = static_cast< size_t >(-1);

  namespace details
  {
    template< class T >
    void destructor(byte* lhs) noexcept
    {
      reinterpret_cast< T* >(lhs)->~T();
    }
    template< bool Nothrow, class T >
    void copy_ctor(byte* lhs, const byte* rhs) noexcept(Nothrow)
    {
      new(lhs) T(*reinterpret_cast< const T* >(rhs));
    }
    template< bool Nothrow, class T >
    void move_ctor(byte* lhs, byte* rhs) noexcept(Nothrow)
    {
      new(lhs) T(std::move(*reinterpret_cast< T* >(rhs)));
    }
    template< bool Nothrow, class T >
    void copy_assign(byte* lhs, const byte* rhs) noexcept(Nothrow)
    {
      *reinterpret_cast< T* >(lhs) = *reinterpret_cast< const T* >(rhs);
    }
    template< bool Nothrow, class T >
    void move_assign(byte* lhs, byte* rhs) noexcept(Nothrow)
    {
      *reinterpret_cast< T* >(lhs) = std::move(*reinterpret_cast< T* >(rhs));
    }

    template< class T >
    struct ArrConvertChecker
    {
      T value[1];
    };
    template< class Src, class Dest, class = void >
    struct is_inarray_constructible: std::false_type
    {};
    template< class Src, class Dest >
    struct is_inarray_constructible< Src, Dest, void_t< decltype(ArrConvertChecker< Dest >{{std::declval< Src >()}}) > >: std::true_type
    {};
    template< class Src, class Dest >
    constexpr bool is_inarray_constructible_v = is_inarray_constructible< Src, Dest >::value;
  }
  template< class T, class U, class... Types >
  struct find_convertible
  {
    static constexpr bool is_convertible = details::is_inarray_constructible_v< T, U >;
    static constexpr size_t value = is_convertible ? 0 : 1 + find_convertible< T, Types... >::value;
    static_assert(!is_convertible || (find_convertible< T, Types... >::value == sizeof...(Types)));
  };
  template< class T, class U >
  struct find_convertible< T, U >
  {
    static constexpr size_t value = !details::is_inarray_constructible_v< T, U >;
  };
}

#endif

#ifndef VARIANT_TOOLS_HPP
#define VARIANT_TOOLS_HPP

#include <type_traits>
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
    template< class T >
    void copy_function(byte* data, const byte* rhs)
    {
      new (data) T(*reinterpret_cast< const T*& >(rhs));
    }
    using copier_t = void (*)(byte*, const byte*);
    template< class T >
    void move_function(byte* data, byte* rhs)
    {
      new(data) T(std::move(*reinterpret_cast< T* >(rhs)));
    }
    using mover_t = void (*)(byte*, byte*);
    template< class T >
    void destructor_function(byte* data)
    {
      reinterpret_cast< T* >(data)->~T();
    }
    using destructor_t = void (*)(byte*);
  }

  template< class U, class T >
  constexpr size_t find_uniq_type_in_pack()
  {
    return !std::is_same< U, T >::value;
  }
  template< class U, class T1, class T2, class... Types >
  constexpr size_t find_uniq_type_in_pack()
  {
    if (std::is_same< U, T1 >::value)
    {
      static_assert(find_uniq_type_in_pack< U, T2, Types... >() == 1 + sizeof...(Types));
      return 0;
    }
    return 1 + find_uniq_type_in_pack< U, T2, Types... >();
  }

  template< class T >
  struct in_place_type_t
  {};
  template< size_t N >
  struct in_place_index_t
  {};
}

#endif

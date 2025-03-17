#include <string>
#include <boost/test/unit_test.hpp>
#include "variant.hpp"

/*struct A
{
  A()
  {
    std::cout << "A()\n";
    constr = 1;
  }
  A(const A&)
  {
    std::cout << "A(const A&)\n";
    constr = 2;
  }
  A(A&&)
  {
    std::cout << "A(A&&)\n";
    constr = 3;
  }
  ~A()
  {
    std::cout << constr << ": ~A()\n";
  }
  A& operator=(const A&)
  {
    std::cout << "A::operator=(const A&)\n";
    constr = 4;
    return *this;
  }
  A& operator=(A&&)
  {
    std::cout << "A::operator=(A&&)\n";
    constr = 5;
    return *this;
  }
  int constr = 0;
};
/*struct A
{};*/
template< size_t Index... >
struct index_sequence
{};
template<>
struct index_sequence< 0 >
{};

template< size_t N >
using make_index_sequence = make_index_sequence< N - 1 >;


namespace details
{
  template< class T >
  struct ArrConvertChecker
  {
    T value[1];
  };
  template< class Src, class Dest, class = void >
  struct is_inarray_constructible: std::false_type
  {};
  template< class Src, class Dest >
  struct is_inarray_constructible< Src, Dest,
        void_t< decltype(ArrConvertChecker< Dest >{{std::declval< Src >()}}) > >: std::true_type
  {};
  template< class Src, class Dest >
  constexpr bool is_inarray_constructible_v = is_inarray_constructible< Src, Dest >::value;

  template< size_t N, class T, class Type, bool = is_inarray_constructible_v< T, Type > >
  struct builds_correct
  {
    void resolve_overload() = delete;
  };
  template< size_t N, class T, class Type >
  struct builds_correct< N, T, Type, true >
  {
    std::integral_constant< size_t, N > resolve_overload(Type);
  };
  template< class T, class Type >
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

BOOST_AUTO_TEST_SUITE(S2_variant_test)

BOOST_AUTO_TEST_CASE(print_info_test)
{
  /*rychkov::Variant< A, int32_t, char > variant;
  *rychkov::get_if< A >(&variant) = A();
  rychkov::Variant< A, int32_t, char, A > variant2{rychkov::in_place_index_t< 3 >()};
  rychkov::Variant< A, int32_t, char > variant3{rychkov::in_place_type_t< A >()};
  variant3 = variant;
  variant3 = std::move(variant);
  variant3 = 934;
  if (rychkov::holds_alternative< int >(variant3))
  {
    std::cout << rychkov::get< 1 >(variant3) << '\n';
  }
  rychkov::Variant< A, int32_t, char > variant4 = std::move(variant3);
  rychkov::Variant< int32_t, A, char > variant5;
  variant5.emplace< A >();
  variant5.emplace< 2 >('!');
  std::cout << rychkov::get< char >(variant5) << '\n';
  rychkov::Variant< int32_t, A, char > variant6(72);
  rychkov::Variant< int32_t, A, char > variant7(variant6);
  std::cout << rychkov::get< int >(variant7) << '\n';
  rychkov::Variant< char, std::string > variant8 = "works";
  variant8 = "works twice";
  std::cout << rychkov::get< std::string >(variant8) << '\n';
  std::cout << (size_t)(rychkov::get_if< char >(&variant8)) << '\n';
  //std::cout << rychkov::get< char >(variant8) << '\n';*/
  //
}

BOOST_AUTO_TEST_SUITE_END()

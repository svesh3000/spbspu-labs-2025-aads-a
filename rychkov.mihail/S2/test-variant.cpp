#include <string>
#include <boost/test/unit_test.hpp>
#include <functional.hpp>
#include "variant.hpp"

namespace rychkov
{
  namespace test_visit
  {
    struct TestStruct
    {
      int field = 0;
      template< class T >
      T add(T n, T m) noexcept(noexcept(n + m))
      {
        return n + m;
      }
    };
    static_assert(is_invocable_v< decltype(&TestStruct::add< int >), TestStruct, int, int >, "");
    static_assert(is_invocable_v< decltype(&TestStruct::field), TestStruct >, "");

    template< class T, class... Types >
    struct sum
    {
      using type = decltype(std::declval< T >() + std::declval< typename sum< Types... >::type >());
      type operator()(T num, Types... nums)
      {
        return num + sum< Types... >()(nums...);
      }
    };
    template< class T >
    struct sum< T >
    {
      using type = T;
      type operator()(T num)
      {
        return num;
      }
    };
    struct Adder
    {
      template< class... Types >
      typename sum< Types... >::type operator()(Types... nums)
      {
        return sum< Types... >()(nums...);
      }
    };
    static_assert(is_invocable_v< Adder, int >, "");
    static_assert(std::is_same< invoke_result_t< Adder, int >, int >::value, "");
    static_assert(!is_nothrow_invocable_v< Adder, int >, "");
  }
}

BOOST_AUTO_TEST_SUITE(S2_variant_test)

BOOST_AUTO_TEST_CASE(print_info_test)
{
  rychkov::Variant< int, char > variant;
  rychkov::Variant< int, char, int > variant2{rychkov::in_place_index_t< 2 >()};
  rychkov::Variant< int, char > variant3{rychkov::in_place_type_t< int >()};
  variant3 = variant;
  variant3 = std::move(variant);
  variant3 = 934;
  rychkov::Variant< int, char > variant4 = std::move(variant3);
  rychkov::Variant< int, char > variant5;
  variant5.emplace< 1 >('!');
  rychkov::Variant< int, char > variant6(72);
  rychkov::Variant< int, char > variant7(variant6);
  rychkov::Variant< char, std::string > variant8 = "works";
  variant8 = "works twice";
  variant = 59;

  rychkov::test_visit::Adder adder{};
  BOOST_TEST(adder(1,2,3,4) == 10);
  BOOST_TEST(rychkov::visit< int >(adder, variant, variant4, variant) == 59*2 + 934);
}

BOOST_AUTO_TEST_SUITE_END()

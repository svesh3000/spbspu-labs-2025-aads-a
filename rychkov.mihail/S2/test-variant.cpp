#include <string>
#include <utility>
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

    template< class T >
    T visit(T num)
    {
      return num;
    }
    template< class T, class... Types >
    decltype(std::declval< T >() + visit(std::declval< Types >()...)) visit(T num, Types... nums)
    {
      return num + visit(nums...);
    }
    struct Visitor
    {
      template< class... Types >
      decltype(visit(std::declval< Types >()...)) operator()(Types... nums)
      {
        return visit(nums...);
      }
    };
    static_assert(is_invocable_v< Visitor, int >, "");
    static_assert(std::is_same< invoke_result_t< Visitor, int >, int >::value, "");
    static_assert(!is_nothrow_invocable_v< Visitor, int >, "");
  }

  template< class R, size_t... Actives, class F, class... Variants >
  R invoke_visit(F&& func, Variants... args)
  {
    return invoke_r< R >(func, get< Actives >(args)...);
  }
  template< class T, size_t... Lens >
  struct multidimensional_array
  {
    T data;
  };
  template< class T, size_t Len, size_t... Lens >
  struct multidimensional_array< T, Len, Lens... >
  {
    multidimensional_array< T, Lens... > data[Len];
  };
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
  rychkov::Variant< int32_t, char > variant6(72);
  rychkov::Variant< int32_t, char > variant7(variant6);
  rychkov::Variant< char, std::string > variant8 = "works";
  variant8 = "works twice";
  variant = 997;
  rychkov::invoke_visit< int, 0 >(rychkov::test_visit::Visitor(), variant);
}

BOOST_AUTO_TEST_SUITE_END()

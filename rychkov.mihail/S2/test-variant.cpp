#include <boost/test/unit_test.hpp>
#include <functional.hpp>
#include "variant.hpp"
#include "mem_checker.hpp"

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

#define USER_DEF_CTOR {}
#define USER_DEF_ASSIGN { return *this; }
#define USER_CHECK(trait, name) std::is_##trait< name >() && !std::is_trivially_##trait< name >()

#define TRIV_DEF_CTOR = default;
#define TRIV_DEF_ASSIGN = default;
#define TRIV_CHECK(trait, name) std::is_trivially_##trait< name >()

#define DEL_DEF_CTOR = delete;
#define DEL_DEF_ASSIGN = delete;
#define DEL_CHECK(trait, name) !std::is_##trait< name >()

#define GENERATE_TRAITS(name, copy_ctor, move_ctor, destructor, copy_assign, move_assign) \
  struct name \
  { \
    name() = default; \
    name(const name&) copy_ctor##_DEF_CTOR \
    name(name&&) move_ctor##_DEF_CTOR \
    ~name() destructor##_DEF_CTOR \
    name& operator=(const name&) copy_assign##_DEF_ASSIGN \
    name& operator=(name&&) move_assign##_DEF_ASSIGN \
  };
#define CHECK_TRAITS(name, copy_ctor, move_ctor, destructor, copy_assign, move_assign) \
  static_assert(copy_ctor##_CHECK(copy_constructible, rychkov::Variant< name >), ""); \
  static_assert(move_ctor##_CHECK(move_constructible, rychkov::Variant< name >), ""); \
  static_assert(destructor##_CHECK(destructible, rychkov::Variant< name >), ""); \
  static_assert(copy_assign##_CHECK(copy_assignable, rychkov::Variant< name >), ""); \
  static_assert(move_assign##_CHECK(move_assignable, rychkov::Variant< name >), "")

namespace rychkov
{
  namespace test_variant_traits
  {
    GENERATE_TRAITS(A1, TRIV, TRIV, TRIV, TRIV, TRIV);
    CHECK_TRAITS(A1, TRIV, TRIV, TRIV, TRIV, TRIV);

    GENERATE_TRAITS(A2, USER, TRIV, TRIV, TRIV, TRIV);
    CHECK_TRAITS(A2, USER, TRIV, TRIV, USER, TRIV);
    GENERATE_TRAITS(A3, TRIV, USER, TRIV, TRIV, TRIV);
    CHECK_TRAITS(A3, TRIV, USER, TRIV, TRIV, USER);
    GENERATE_TRAITS(A4, DEL, TRIV, TRIV, TRIV, TRIV);
    CHECK_TRAITS(A4, DEL, TRIV, TRIV, DEL, TRIV);
    GENERATE_TRAITS(A5, TRIV, DEL, TRIV, TRIV, TRIV);
    CHECK_TRAITS(A5, TRIV, TRIV, TRIV, TRIV, TRIV);

    GENERATE_TRAITS(A6, TRIV, TRIV, TRIV, USER, TRIV);
    CHECK_TRAITS(A6, TRIV, TRIV, TRIV, USER, TRIV);
    GENERATE_TRAITS(A7, TRIV, TRIV, TRIV, TRIV, USER);
    CHECK_TRAITS(A7, TRIV, TRIV, TRIV, TRIV, USER);
    GENERATE_TRAITS(A8, TRIV, TRIV, TRIV, DEL, TRIV);
    CHECK_TRAITS(A8, TRIV, TRIV, TRIV, DEL, TRIV);
    GENERATE_TRAITS(A9, TRIV, TRIV, TRIV, TRIV, DEL);
    CHECK_TRAITS(A9, TRIV, TRIV, TRIV, TRIV, TRIV);

    GENERATE_TRAITS(A10, TRIV, TRIV, USER, TRIV, TRIV);
    CHECK_TRAITS(A10, USER, USER, USER, USER, USER);
  }
}

BOOST_AUTO_TEST_SUITE(S2_variant_test)

BOOST_AUTO_TEST_CASE(print_info_test)
{
  rychkov::Variant< int, char > variant1 = 59;
  rychkov::Variant< int, char > variant2 = 934;
  rychkov::test_visit::Adder adder{};
  BOOST_TEST(adder(1, 2, 3, 4) == 10);
  BOOST_TEST(rychkov::visit< int >(adder, variant1, variant2, variant1) == 59 * 2 + 934);
}

BOOST_AUTO_TEST_CASE(get_test)
{
  using rychkov::test_variant_traits::A1;
  using rychkov::test_variant_traits::A2;
  using rychkov::test_variant_traits::A3;
  rychkov::MemTrack< A1, A2, A3 > protector{};
  constexpr rychkov::Variant< A2, int, char > constexpr_var_1;
  constexpr rychkov::Variant< A3, int, char > constexpr_var_2;
  rychkov::Variant< rychkov::MemChecker< A2 >, int, char > var1;
  rychkov::Variant< rychkov::MemChecker< A2 >, int, char > var2 = std::move(var1);
  rychkov::Variant< int, char > variant;
  rychkov::Variant< rychkov::MemChecker< A1 >, int, char, int > variant2{rychkov::in_place_index_t< 0 >()};
  rychkov::Variant< int, char > variant3{rychkov::in_place_type_t< int >()};
  variant3 = variant;
  variant3 = std::move(variant);
  variant3 = 934;
  rychkov::Variant< int, char > variant4 = std::move(variant3);
  rychkov::Variant< int, char > variant5;
  variant5.emplace< 1 >('!');
  rychkov::Variant< int, char > variant6(72);
  rychkov::Variant< int, char > variant7('l');
  rychkov::Variant< rychkov::MemChecker< A1 >, char > variant8 = rychkov::MemChecker< A1 >();
  variant = 59;
}

BOOST_AUTO_TEST_SUITE_END()

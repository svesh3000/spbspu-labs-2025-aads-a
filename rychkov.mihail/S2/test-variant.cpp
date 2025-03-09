#include <boost/test/unit_test.hpp>
#include "variant.hpp"

struct A
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
  int constr = 0;
};

BOOST_AUTO_TEST_SUITE(S2_variant_test)

BOOST_AUTO_TEST_CASE(print_info_test)
{
  rychkov::Variant< A, int32_t, char > variant;
  rychkov::Variant< A, int32_t, char, A > variant2 = {rychkov::in_place_index_t< 3 >()};
  rychkov::Variant< A, int32_t, char > variant3 = {rychkov::in_place_type_t< A >()};
  rychkov::Variant< A, int32_t, char > variant4 = std::move(variant3);
}

BOOST_AUTO_TEST_SUITE_END()

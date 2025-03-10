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

BOOST_AUTO_TEST_SUITE(S2_variant_test)

BOOST_AUTO_TEST_CASE(print_info_test)
{
  rychkov::Variant< A, int32_t, char > variant;
  rychkov::Variant< A, int32_t, char, A > variant2 = {rychkov::in_place_index_t< 3 >()};
  rychkov::Variant< A, int32_t, char > variant3 = {rychkov::in_place_type_t< A >()};
  rychkov::Variant< A, int32_t, char > variant4 = std::move(variant3);
  *rychkov::get_if< A >(&variant3) = A();
  variant2 = '3';
  variant2 = 9;
  if (rychkov::holds_alternative< int >(variant2))
  {
    std::cout << rychkov::get< 1 >(variant2) << '\n';
  }
}

BOOST_AUTO_TEST_SUITE_END()

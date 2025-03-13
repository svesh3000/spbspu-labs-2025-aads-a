#include <string>
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
/*struct A
{};*/

BOOST_AUTO_TEST_SUITE(S2_variant_test)

BOOST_AUTO_TEST_CASE(print_info_test)
{
  rychkov::Variant< A, int32_t, char > variant;
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
}

BOOST_AUTO_TEST_SUITE_END()

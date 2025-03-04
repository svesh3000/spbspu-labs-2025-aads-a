#include "test_utils.hpp"

BOOST_AUTO_TEST_SUITE(S1_constructors_test)

BOOST_AUTO_TEST_CASE(emplace_test)
{
  rychkov::List< int > list;
  BOOST_TEST(list.emplace(list.begin(), 5) == 5);
  BOOST_TEST(list.emplace(list.begin(), 2) == 2);
  BOOST_TEST(list.emplace(list.end(), 6) == 6);
  BOOST_TEST(list.emplace(++(++list.begin()), 8) == 8);
  BOOST_TEST(list.emplace(++(++list.begin()), 0) == 0);
  rychkov::fullCompare(list, {2, 5, 0, 8, 6});
}
BOOST_AUTO_TEST_CASE(emplace_spec_test)
{
  rychkov::List< int > list;
  BOOST_TEST(list.emplace_front(5) == 5);
  BOOST_TEST(list.emplace_front(2) == 2);
  BOOST_TEST(list.emplace_back(6) == 6);
  rychkov::fullCompare(list, {2, 5, 6});
}

BOOST_AUTO_TEST_SUITE_END()

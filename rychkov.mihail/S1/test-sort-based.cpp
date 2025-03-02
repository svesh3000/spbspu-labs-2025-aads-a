#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(S1_sort_based_test)

BOOST_AUTO_TEST_CASE(sort_test)
{
  rychkov::List< int > list = {3, 6, 4, -1, 7};
  rychkov::List< int > expected = {-1, 3, 4, 6, 7};
  list.sort();
}
BOOST_AUTO_TEST_CASE(reverse_test)
{
  rychkov::List< int > list = {3, 6, 4, -1, 7};
  rychkov::List< int > expected = {list.rbegin(), list.rend()};
  list.reverse();
  BOOST_TEST(list == expected);
  BOOST_TEST(list.front() == expected.front());
  BOOST_TEST(list.back() == expected.back());
  expected = {7, -1, 4, 6, 3};
  BOOST_TEST(list == expected);
  BOOST_TEST(list.front() == expected.front());
  BOOST_TEST(list.back() == expected.back());
}

BOOST_AUTO_TEST_SUITE_END()

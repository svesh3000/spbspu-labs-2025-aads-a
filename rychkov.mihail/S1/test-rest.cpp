#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(S1_rest_test)

BOOST_AUTO_TEST_CASE(comparison_test)
{
  rychkov::List< int > list1 = {1, 4, 2, 7};
  rychkov::List< int > list2 = {1, 3, 0, 5, 8};
  rychkov::List< int > list3 = {0, 3, 0, 5, 8};
  BOOST_TEST(list2 <= list1);
  BOOST_TEST(!(list2 < list1));
  BOOST_TEST(list3 < list1);
  BOOST_TEST(list1 >= list2);
  BOOST_TEST(!(list1 > list2));
  BOOST_TEST(list1 > list3);
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

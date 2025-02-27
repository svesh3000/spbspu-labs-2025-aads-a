#include <array>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(S1_constructors_test)

BOOST_AUTO_TEST_CASE(emplace_test)
{
  rychkov::List< int > list;
  BOOST_TEST(list.emplace(list.begin(), 5) == 5);
  BOOST_TEST(list.emplace(list.begin(), 2) == 2);
  BOOST_TEST(list.emplace(list.end(), 6) == 6);
  rychkov::List< int > expected = {2, 5, 6};
  BOOST_TEST(list == expected);
}
BOOST_AUTO_TEST_CASE(emplace_spec_test)
{
  rychkov::List< int > list;
  BOOST_TEST(list.emplace_front(5) == 5);
  BOOST_TEST(list.emplace_front(2) == 2);
  BOOST_TEST(list.emplace_back(6) == 6);
  rychkov::List< int > expected = {2, 5, 6};
  BOOST_TEST(list == expected);
}
BOOST_AUTO_TEST_CASE(splice_all_lvalue_test)
{
  rychkov::List< int > expected = {3, 7, 1, 0};
  rychkov::List< int > list = expected;
  rychkov::List< int > list2;
  list2.splice(list2.begin(), list);
  BOOST_TEST(list2 == expected);
}
BOOST_AUTO_TEST_CASE(splice_part_test)
{
  rychkov::List< int > list1 = {3, 7, 1, 0};
  rychkov::List< int > list2;
  list2.splice(list2.begin(),list1, list1.begin(), ++(++list1.begin()));
  rychkov::List< int > expected = {1, 0};
  BOOST_TEST(list1 == expected);
  expected = {3, 7};
  BOOST_TEST(list2 == expected);
}

BOOST_AUTO_TEST_SUITE_END()

#include <array>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(S1_constructors_test)

BOOST_AUTO_TEST_CASE(empty_test)
{
  rychkov::List< int > list;
  BOOST_TEST(list.size() == 0);
  BOOST_TEST(list.empty());
  BOOST_REQUIRE(list.begin() == list.end());
}
BOOST_AUTO_TEST_CASE(initializer_list_test)
{
  int expected[] = {2, 5, 3, 9};
  rychkov::List< int > list = {2, 5, 3, 9};
  BOOST_TEST(list.size() == std::size(expected));
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.front() == *expected);
  BOOST_TEST(list.back() == expected[std::size(expected) - 1]);

  BOOST_TEST(std::equal(list.begin(), list.end(), expected, expected + std::size(expected)));
}
BOOST_AUTO_TEST_CASE(S1_array_ptrs_test)
{
  int expected[] = {2, 5, 3, 9};
  rychkov::List< int > list(expected, expected + std::size(expected));
  BOOST_TEST(list.size() == 4);
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.front() == *expected);
  BOOST_TEST(list.back() == expected[std::size(expected) - 1]);

  BOOST_TEST(std::equal(list.begin(), list.end(), expected, expected + std::size(expected)));
}
BOOST_AUTO_TEST_CASE(fill_test)
{
  constexpr int initValue = 4;
  constexpr size_t initSize = 9;
  rychkov::List< int > list(initValue, initSize);
  BOOST_TEST(list.size() == initSize);
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.front() == initValue);
  BOOST_TEST(list.back() == initValue);

  size_t len = 0;
  for (int i : list)
  {
    BOOST_TEST(len < initSize);
    BOOST_TEST(i == initValue);
    ++len;
  }
}
BOOST_AUTO_TEST_CASE(copy_test)
{
  rychkov::List< int > list = {2, 5, 3, 9};
  rychkov::List< int > list2 = list;
  BOOST_TEST(list == list2);
}
BOOST_AUTO_TEST_CASE(move_test)
{
  int expected[] = {2, 5, 3, 9};
  rychkov::List< int > list(expected, expected + std::size(expected));
  rychkov::List< int > list2 = std::move(list);
  BOOST_TEST(std::equal(list2.begin(), list2.end(), expected, expected + std::size(expected)));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(S1_assignment_test)

BOOST_AUTO_TEST_CASE(copy_test)
{
  rychkov::List< int > list = {1, 2, 3};
  rychkov::List< int > list2;
  list2 = list;
  BOOST_TEST(list == list2);
}
BOOST_AUTO_TEST_CASE(move_test)
{
  rychkov::List< int > list = {7, 3, 5};
  rychkov::List< int > list2;
  list2 = std::move(list);
  rychkov::List< int > list3 = {7, 3, 5};
  BOOST_TEST(list2 == list3);
}
BOOST_AUTO_TEST_CASE(initializer_list_test)
{
  rychkov::List< int > list = {7, 3, 5};
  rychkov::List< int > list2;
  list2 = {7, 3, 5};
  BOOST_TEST(list == list2);
}

BOOST_AUTO_TEST_SUITE_END()

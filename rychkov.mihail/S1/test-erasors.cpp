#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(S1_erasors_test)

BOOST_AUTO_TEST_CASE(erase_single_test)
{
  rychkov::List< int > list = {3, 6, 4, -1, 7};
  rychkov::List< int > expected = {3, 4, -1, 7};
  BOOST_TEST(*list.erase(++list.begin()) == 4);
  BOOST_TEST(list == expected);
  BOOST_TEST(list.front() == expected.front());
  BOOST_TEST(list.back() == expected.back());
}
BOOST_AUTO_TEST_CASE(erase_multiple_test)
{
  rychkov::List< int > list = {3, 6, 4, -1, 7};
  rychkov::List< int > expected = {4, -1, 7};
  BOOST_TEST(*list.erase(list.begin(), ++(++list.begin())) == 4);
  BOOST_TEST(list == expected);
  BOOST_TEST(list.front() == expected.front());
  BOOST_TEST(list.back() == expected.back());
}
BOOST_AUTO_TEST_CASE(remove_test)
{
  rychkov::List< int > list = {3, 3, 4, -1, 3, 7, 3};
  rychkov::List< int > expected = {4, -1, 7};
  BOOST_TEST(list.remove(3) == 4);
  BOOST_TEST(list == expected);
  BOOST_TEST(list.front() == expected.front());
  BOOST_TEST(list.back() == expected.back());
}

BOOST_AUTO_TEST_SUITE_END()

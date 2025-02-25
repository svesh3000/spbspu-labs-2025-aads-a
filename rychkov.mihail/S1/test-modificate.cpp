#include <array>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(S1_constructors_test)

BOOST_AUTO_TEST_CASE(emplace_test)
{
  rychkov::List< int > list;
  list.emplace(list.begin(), 5);
  list.emplace(list.begin(), 2);
  list.emplace(list.end(), 6);
  rychkov::List< int > expected = {2, 5, 6};
}
BOOST_AUTO_TEST_CASE(emplace_spec_test)
{
  rychkov::List< int > list;
  list.emplace_front(5);
  list.emplace_front(2);
  list.emplace_back(6);
  rychkov::List< int > expected = {2, 5, 6};
}

BOOST_AUTO_TEST_SUITE_END()

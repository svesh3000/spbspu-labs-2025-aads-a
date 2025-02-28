#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_CASE(test_element_access)
{
  List< int > list;
  list.push_front(0);
  list.push_front(1);
  list.push_front(2);
  BOOST_TEST(list.front() == 2);
  BOOST_TEST(list.back() == 0);
}
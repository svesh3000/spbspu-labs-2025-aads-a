#include <boost/test/unit_test.hpp>
#include "forward_list.hpp"

BOOST_AUTO_TEST_CASE(boost_test)
{
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(push_back_and_size_test)
{
  asafov::Forward_list<size_t> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  BOOST_TEST(list.size() == 4);
}

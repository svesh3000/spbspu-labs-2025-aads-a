#include <boost/test/unit_test.hpp>
#include "fwdlist-ring.hpp"

BOOST_AUTO_TEST_CASE(fill_constructor)
{
  sveshnikov::FwdList< int > list1(10, 5);
  BOOST_TEST(list1.getSize() == 10);
  sveshnikov::FwdList< int > list2(0, 5);
  BOOST_TEST(list2.getSize() == 0);
}
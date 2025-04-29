#include <boost/test/unit_test.hpp>
#include "two-three-tree.h"

BOOST_AUTO_TEST_CASE(test_iterator)
{
  savintsev::TwoThreeTree< int, int > map;
  map[1] = 10;
  BOOST_CHECK(map[1] == 10);
}

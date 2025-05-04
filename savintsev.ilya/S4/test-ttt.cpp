#include <boost/test/unit_test.hpp>
#include "two-three-tree.h"

BOOST_AUTO_TEST_CASE(test_iterator)
{
  savintsev::TwoThreeTree< int, int > map;
  map[1] = 10;
  map[2] = 20;
  map[1] = 30;
  map[5] = 50;
  map[3] = 33;
  map[0] = 5;
  map[4] = 40;
  BOOST_TEST(map[1] == 30);
  BOOST_TEST(map[2] == 20);
  BOOST_TEST(map[5] == 50);
  BOOST_TEST(map[3] == 33);
  BOOST_TEST(map[0] == 5);
  BOOST_TEST(map[4] == 40);
  for (auto it = map.begin(); it != map.end(); ++it)
  {
    std::cout << it->first << " " << it->second << std::endl;
  }
}

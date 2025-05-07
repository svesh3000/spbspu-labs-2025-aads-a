#include <boost/test/unit_test.hpp>
#include "two-three-tree.h"

BOOST_AUTO_TEST_CASE(test_iterator)
{
  savintsev::TwoThreeTree< int, int > map;
  map.insert({1, 10});
  BOOST_TEST(map[1] == 10);
  map[1] = 111;
  map[2] = 20;
  map[10] = 100;
  map[5] = 50;
  map[8] = 80;
  //map[0] = 5;
  //map[4] = 40;
  BOOST_TEST(map[1] == 111);
  BOOST_TEST(map[2] == 20);
  BOOST_TEST(map[10] == 100);
  BOOST_TEST(map[5] == 50);
  BOOST_TEST(map[8] == 80);
  //BOOST_TEST(map[0] == 5);
  //BOOST_TEST(map[4] == 40);
  for (auto it = map.begin(); it != map.end(); ++it)
  {
    std::cout << it->first << " " << it->second << std::endl;
  }
}

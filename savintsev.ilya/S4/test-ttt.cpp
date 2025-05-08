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
  map[18] = 180;
  map[20] = 200;
  map[0] = 11;
  map[-1] = -10;
  map[6] = 60;
  map[7] = 70;
  BOOST_TEST(map[1] == 111);
  BOOST_TEST(map[2] == 20);
  BOOST_TEST(map[10] == 100);
  BOOST_TEST(map[5] == 50);
  BOOST_TEST(map[8] == 80);
  BOOST_TEST(map[18] == 180);
  BOOST_TEST(map[20] == 200);
  BOOST_TEST(map[0] == 11);
  BOOST_TEST(map[-1] == -10);
  BOOST_TEST(map[6] == 60);
  BOOST_TEST(map[7] == 70);
}

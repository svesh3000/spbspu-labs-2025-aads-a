#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <mem_checker.hpp>
#include "map.hpp"

BOOST_AUTO_TEST_SUITE(S4_map_test)

BOOST_AUTO_TEST_CASE(empty_test)
{
  rychkov::Map< int, char > map;
  BOOST_TEST(map.empty());
  BOOST_TEST((map.find(234) == map.end()));
  BOOST_TEST(!map.contains(93));
  BOOST_TEST((map.begin() == map.end()));
  BOOST_CHECK_THROW(map.at(0), std::out_of_range);
}
BOOST_AUTO_TEST_CASE(access_test)
{
  rychkov::Map< int, char > map = {{0, '1'}, {3, '2'}, {-1, '3'}, {2, '4'}};
  BOOST_TEST(map.size() == 4);
  BOOST_TEST((map.find(234) == map.end()));
  BOOST_TEST((map.find(-1) == map.begin()));
  BOOST_TEST(!map.contains(-44));
  BOOST_TEST(map.contains(3));
  BOOST_TEST((map.begin() != map.end()));
  BOOST_CHECK_THROW(map.at(7), std::out_of_range);
  BOOST_CHECK_THROW(map.at(1), std::out_of_range);
  BOOST_CHECK(map.lower_bound(2)->first == 2);
  BOOST_CHECK(map.upper_bound(2)->first == 3);
  map[9] = '5';
  BOOST_CHECK(map[9] == '5');
  map[1] = '6';
  BOOST_CHECK(map[1] == '6');
  BOOST_CHECK(map[3] == '2');
}

BOOST_AUTO_TEST_SUITE_END()

#include <stdexcept>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <boost/test/unit_test.hpp>
#include <mem_checker.hpp>
#include "map.hpp"
#include "set.hpp"

BOOST_AUTO_TEST_SUITE(S4_map_test)

BOOST_AUTO_TEST_CASE(multimap_test)
{
  rychkov::MultiMap< int, int > multimap;
  for (int i = 10; i > 0; i--)
  {
    multimap.try_emplace(i);
  }
  for (int i = 10; i > 0; i--)
  {
    multimap.try_emplace(i);
  }
  multimap.erase(2);
}

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
  BOOST_TEST(map.at(3) == '2');
  BOOST_TEST(map.lower_bound(2)->first == 2);
  BOOST_TEST(map.upper_bound(2)->first == 3);
  map[9] = '5';
  BOOST_TEST(map[9] == '5');
  map[1] = '6';
  BOOST_TEST(map[1] == '6');
  BOOST_TEST(map[3] == '2');
}
BOOST_AUTO_TEST_CASE(erase_test)
{
  rychkov::Map< int, char > map = {{0, '1'}, {2, '2'}, {1, '3'}, {5, '4'}, {-3, '5'}, {4, '6'}, {-2, '7'}};
  BOOST_TEST(map.erase(map.find(0))->first == 1);
  BOOST_TEST(map.erase(2) == 1);
  BOOST_TEST(map.erase(-1) == 0);
  BOOST_TEST(map.erase(4) == 1);
  BOOST_TEST(map.erase(1) == 1);
  BOOST_TEST((map.erase(map.begin(), map.end()) == map.end()));
}
BOOST_AUTO_TEST_CASE(random_test)
{
  std::mt19937 engine;
  engine.seed(std::chrono::system_clock::now().time_since_epoch().count());
  constexpr size_t input_size = 1024;
  int data[input_size];
  rychkov::MapBase< int, char, std::less<>, 2, false, false > map;
  for (int& i: data)
  {
    i = engine();
    map.emplace(i, '\0');
  }
  std::sort(data, data + input_size);
  size_t size = std::unique(data, data + input_size) - data;
  struct equal_to_key
  {
    bool operator()(const std::pair< int, char >& lhs, const int& rhs)
    {
      return lhs.first == rhs;
    }
  };
  BOOST_TEST(std::equal(map.begin(), map.end(), data, equal_to_key{}));
  for (; size > 0; size--)
  {
    std::uniform_int_distribution< size_t > range(0, size - 1);
    size_t id = range(engine);
    decltype(map)::iterator next = map.erase(map.find(data[id]));
    std::remove(data, data + size, data[id]);
    if (id == size - 1)
    {
      BOOST_TEST((next == map.end()));
    }
    else
    {
      BOOST_TEST(next->first == data[id]);
    }
    BOOST_TEST(std::equal(map.begin(), map.end(), data, equal_to_key{}));
    BOOST_TEST(map.size() == size - 1);
  }
}

BOOST_AUTO_TEST_SUITE_END()

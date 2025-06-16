#include <boost/test/unit_test.hpp>
#include <set>
#include <tree/avlTee.hpp>
#include "key_sum.hpp"

struct SimpleCollector
{
  void operator()(const std::pair< const int, std::string > & kv)
  {
    keys.push_back(kv.first);
    values.push_back(kv.second);
  }
  std::vector< int > keys;
  std::vector< std::string > values;
};

BOOST_AUTO_TEST_CASE(test_simple_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  tree[2] = "two";
  SimpleCollector collector;
  tree.traverse_lnr(collector);
  BOOST_TEST(collector.keys.size() == 2);
  BOOST_TEST(collector.values.size() == 2);
}

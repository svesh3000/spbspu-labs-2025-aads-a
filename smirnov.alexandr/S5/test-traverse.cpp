#include <boost/test/unit_test.hpp>
#include <set>
#include <tree/avlTee.hpp>
#include "key_sum.hpp"

BOOST_AUTO_TEST_CASE(test_lnr_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[5] = "five";
  tree[3] = "three";
  tree[7] = "seven";
  tree[2] = "two";
  tree[4] = "four";
  tree[6] = "six";
  tree[8] = "eight";
  smirnov::KeySum collector;
  tree.traverse_lnr(collector);
  BOOST_TEST(collector.result == 35);
  std::set< std::string > expected {" two", " three", " four", " five", " six", " seven", " eight"};
  std::istringstream iss(collector.elems);
  std::set< std::string > actual;
  std::string token;
  while (iss >> token)
  {
    actual.insert(" " + token);
  }
  BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(test_rnl_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[5] = "five";
  tree[3] = "three";
  tree[7] = "seven";
  tree[2] = "two";
  tree[4] = "four";
  tree[6] = "six";
  tree[8] = "eight";
  smirnov::KeySum collector;
  tree.traverse_rnl(collector);
  BOOST_TEST(collector.result == 35);
  std::set< std::string > expected {" two", " three", " four", " five", " six", " seven", " eight"};
  std::istringstream iss(collector.elems);
  std::set< std::string > actual;
  std::string token;
  while (iss >> token)
  {
    actual.insert(" " + token);
  }
  BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(test_breadth_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[5] = "five";
  tree[3] = "three";
  tree[7] = "seven";
  tree[2] = "two";
  tree[4] = "four";
  tree[6] = "six";
  tree[8] = "eight";
  smirnov::KeySum collector;
  tree.traverse_breadth(collector);
  BOOST_TEST(collector.result == 35);
  std::set< std::string > expected {" five", " three", " seven", " two", " four", " six", " eight"};
  std::istringstream iss(collector.elems);
  std::set< std::string > actual;
  std::string token;
  while (iss >> token)
  {
    actual.insert(" " + token);
  }
  BOOST_TEST(actual == expected);
}

BOOST_AUTO_TEST_CASE(test_empty_tree_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  smirnov::KeySum lnr_collector;
  tree.traverse_lnr(lnr_collector);
  BOOST_TEST(lnr_collector.result == 0);
  BOOST_TEST(lnr_collector.elems.empty());
  smirnov::KeySum rnl_collector;
  tree.traverse_rnl(rnl_collector);
  BOOST_TEST(rnl_collector.result == 0);
  BOOST_TEST(rnl_collector.elems.empty());
  smirnov::KeySum breadth_collector;
  tree.traverse_breadth(breadth_collector);
  BOOST_TEST(breadth_collector.result == 0);
  BOOST_TEST(breadth_collector.elems.empty());
}

BOOST_AUTO_TEST_CASE(test_single_node_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  smirnov::KeySum collector;
  tree.traverse_lnr(collector);
  BOOST_TEST(collector.result == 1);
  BOOST_TEST(collector.elems == " one");
  collector = smirnov::KeySum();
  tree.traverse_rnl(collector);
  BOOST_TEST(collector.result == 1);
  BOOST_TEST(collector.elems == " one");
  collector = smirnov::KeySum();
  tree.traverse_breadth(collector);
  BOOST_TEST(collector.result == 1);
  BOOST_TEST(collector.elems == " one");
}

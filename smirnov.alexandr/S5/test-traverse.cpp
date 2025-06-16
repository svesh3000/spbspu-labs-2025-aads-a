#include <boost/test/unit_test.hpp>
#include <set>
#include <tree/avlTee.hpp>

struct TestData
{
  void operator()(const std::pair< const int, std::string > & kv)
  {
    keys.push_back(kv.first);
    values.push_back(kv.second);
  }
  void clear()
  {
    keys.clear();
    values.clear();
  }
  std::vector< int > keys;
  std::vector< std::string > values;
};

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
  TestData data;
  tree.traverse_lnr(data);
  BOOST_TEST(data.keys.size() == 7u);
  BOOST_TEST(data.values.size() == 7u);
  bool is_sorted = std::is_sorted(data.keys.begin(), data.keys.end());
  BOOST_TEST(is_sorted);
  std::set< int > unique_keys(data.keys.begin(), data.keys.end());
  BOOST_TEST(unique_keys.size() == 7u);
  BOOST_TEST(unique_keys.count(2) == 1u);
  BOOST_TEST(unique_keys.count(3) == 1u);
  BOOST_TEST(unique_keys.count(4) == 1u);
  BOOST_TEST(unique_keys.count(5) == 1u);
  BOOST_TEST(unique_keys.count(6) == 1u);
  BOOST_TEST(unique_keys.count(7) == 1u);
  BOOST_TEST(unique_keys.count(8) == 1u);
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
  TestData data;
  tree.traverse_rnl(data);
  BOOST_TEST(data.keys.size() == 7u);
  BOOST_TEST(data.values.size() == 7u);
  bool is_reverse_sorted = std::is_sorted(data.keys.rbegin(), data.keys.rend());
  BOOST_TEST(is_reverse_sorted);
  std::set< int > unique_keys(data.keys.begin(), data.keys.end());
  BOOST_TEST(unique_keys.size() == 7u);
  BOOST_TEST(unique_keys.count(2) == 1u);
  BOOST_TEST(unique_keys.count(3) == 1u);
  BOOST_TEST(unique_keys.count(4) == 1u);
  BOOST_TEST(unique_keys.count(5) == 1u);
  BOOST_TEST(unique_keys.count(6) == 1u);
  BOOST_TEST(unique_keys.count(7) == 1u);
  BOOST_TEST(unique_keys.count(8) == 1u);
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
  TestData data;
  tree.traverse_breadth(data);
  BOOST_TEST(data.keys.size() == 7u);
  BOOST_TEST(data.values.size() == 7u);
  BOOST_TEST(data.keys[0] == 5);
  std::set< int > unique_keys(data.keys.begin(), data.keys.end());
  BOOST_TEST(unique_keys.size() == 7u);
  BOOST_TEST(unique_keys.count(2) == 1u);
  BOOST_TEST(unique_keys.count(3) == 1u);
  BOOST_TEST(unique_keys.count(4) == 1u);
  BOOST_TEST(unique_keys.count(5) == 1u);
  BOOST_TEST(unique_keys.count(6) == 1u);
  BOOST_TEST(unique_keys.count(7) == 1u);
  BOOST_TEST(unique_keys.count(8) == 1u);
}

BOOST_AUTO_TEST_CASE(test_empty_tree_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  TestData data;
  data.clear();
  tree.traverse_lnr(data);
  BOOST_TEST(data.keys.empty());
  BOOST_TEST(data.values.empty());
  data.clear();
  tree.traverse_rnl(data);
  BOOST_TEST(data.keys.empty());
  BOOST_TEST(data.values.empty());
  data.clear();
  tree.traverse_breadth(data);
  BOOST_TEST(data.keys.empty());
  BOOST_TEST(data.values.empty());
}

BOOST_AUTO_TEST_CASE(test_single_node_traversal)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  TestData data;
  data.clear();
  tree.traverse_lnr(data);
  BOOST_TEST(data.keys.size() == 1u);
  BOOST_TEST(data.keys[0] == 1);
  BOOST_TEST(data.values[0] == "one");
  data.clear();
  tree.traverse_rnl(data);
  BOOST_TEST(data.keys.size() == 1u);
  BOOST_TEST(data.keys[0] == 1);
  BOOST_TEST(data.values[0] == "one");
  data.clear();
  tree.traverse_breadth(data);
  BOOST_TEST(data.keys.size() == 1u);
  BOOST_TEST(data.keys[0] == 1);
  BOOST_TEST(data.values[0] == "one");
}

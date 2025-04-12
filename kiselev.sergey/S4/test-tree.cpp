#include <cstddef>
#include <string>
#include <utility>
#include <boost/test/tools/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include "tree.hpp"

using namespace kiselev;

BOOST_AUTO_TEST_SUITE(tree)

BOOST_AUTO_TEST_CASE(constructors)
{
  RBTree< size_t, std::string > tree;
  BOOST_TEST(tree.size() == 0);
  RBTree< size_t, std::string > inilTree{ { 1, "1" }, { 2, "2" }, { 0, "0" } };
  BOOST_TEST(inilTree.size() == 3);
  RBTree< size_t, std::string > copyTree(inilTree);
  BOOST_TEST(copyTree.size() == 3);
  RBTree< size_t, std::string > moveTree(std::move(copyTree));
  BOOST_TEST(moveTree.size() == 3);
  RBTree< size_t, std::string >::Iterator it = inilTree.begin();
  ++it;
  RBTree< size_t, std::string > rangeTree(it, inilTree.end());
  BOOST_TEST(rangeTree.size() == 2);
}

BOOST_AUTO_TEST_CASE(assignment_operators)
{
  RBTree< size_t, std::string > tree;
  std::initializer_list< std::pair< size_t, std::string > > il = { { 1, "1" }, { 2, "2" }, { 3, "3" } };
  tree = il;
  BOOST_TEST(tree.size() == 3);
  RBTree< size_t, std::string > copyTree;
  copyTree = tree;
  BOOST_TEST(copyTree.size() == 3);
  RBTree< size_t, std::string > moveTree;
  moveTree = std::move(copyTree);
  BOOST_TEST(moveTree.size() == 3);
  BOOST_TEST(copyTree.size() == 0);
}

BOOST_AUTO_TEST_CASE(index_operator_and_at)
{
  RBTree< size_t, std::string > tree({ { 1, "1" }, { 2, "2" }, { 3, "3" } });
  BOOST_TEST(tree[1] == "1");
  tree[4];
  BOOST_TEST(tree.size() == 4);
  BOOST_TEST(tree.at(2) == "2");
}

BOOST_AUTO_TEST_CASE(size_and_empty)
{
  RBTree< size_t, std::string > tree;
  BOOST_TEST(tree.empty());
  tree.insert({ 1, "1" });
  BOOST_TEST(tree.size() == 1);
}

BOOST_AUTO_TEST_CASE(insert_element)
{
  RBTree< size_t, std::string > tree;
  RBTree< size_t, std::string >::Iterator it = tree.insert({ 1, "1" }).first;
  BOOST_TEST((*it).first == 1);
  bool isInserted = tree.insert({ 1, "1" }).second;
  BOOST_TEST(!isInserted);
  std::pair< size_t, std::string > pair1 = { 2, "2" };
  tree.insert(pair1);
  BOOST_TEST(tree.size() == 2);
  const std::pair< size_t, std::string > pair2 = { 3, "3" };
  tree.insert(pair2);
  BOOST_TEST(tree.size() == 3);
}

BOOST_AUTO_TEST_CASE(insert_hint)
{
  RBTree< size_t, std::string > tree({ { 1, "1" }, { 2, "2" }, { 3, "3" } });
  RBTree< size_t, std::string >::Iterator it = tree.begin();
  RBTree< size_t, std::string >::ConstIterator cit = tree.cend();
  tree.insert(it, std::make_pair(4, "4"));
  BOOST_TEST(tree.size() == 4);
  tree.insert(cit, std::make_pair(5, "5"));
  BOOST_TEST(tree.size() == 5);
}

BOOST_AUTO_TEST_CASE(insert_range_and_init)
{
  RBTree< size_t, std::string > tree;
  RBTree< size_t, std::string > tree2({ { 1, "1" }, { 2, "2" }, { 3, "3" } });
  tree.insert(++tree2.begin(), tree2.end());
  BOOST_TEST(tree.size() == 2);
  tree.insert({ { 4, "4" }, { 1, "1" }, { 5, "5" } });
  BOOST_TEST(tree.size() == 5);
}
BOOST_AUTO_TEST_CASE(erase_position)
{
  RBTree< size_t, std::string > tree({ { 1, "1" }, { 2, "2" }, { 3, "3" }, { 4, "4" } });
  RBTree< size_t, std::string >::Iterator it = tree.erase(tree.begin());
  BOOST_CHECK(it == tree.begin());
  it = tree.erase(tree.cbegin());
  BOOST_CHECK(it == tree.begin());
  size_t i = tree.erase(3);
  BOOST_TEST(i == 1);
  i = tree.erase(6);
  BOOST_TEST(i == 0);
  tree = { { 1, "1" }, { 2, "2" }, { 3, "3" } };
  tree.erase(tree.begin(), tree.end());
  BOOST_TEST(tree.empty());
  tree = { { 1, "1" }, { 2, "2" }, { 3, "3" } };
  tree.erase(tree.cbegin(), tree.cend());
  BOOST_TEST(tree.empty());
}
BOOST_AUTO_TEST_SUITE_END();

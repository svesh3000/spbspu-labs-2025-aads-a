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
BOOST_AUTO_TEST_SUITE_END();

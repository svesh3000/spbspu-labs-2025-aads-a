#include <cstddef>
#include <string>
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
BOOST_AUTO_TEST_SUITE_END();

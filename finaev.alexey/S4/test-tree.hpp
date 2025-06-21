#include <boost/test/unit_test.hpp>
#include <sstream>
#include <string>
#include <AVLtree.hpp>

namespace
{
  void printTree(std::ostream& out, const finaev::AVLtree< int, std::string >& tree)
  {
    for (auto it = tree.cBegin(); it != tree.cEnd(); ++it)
    {
      out << it->second;
    }
  }
}

BOOST_AUTO_TEST_CASE(tree_constructors)
{
  finaev::AVLtree< int, std::string > tree;
  BOOST_TEST(tree.empty());
  BOOST_TEST(tree.size() == 0);
  tree.insert({1, "1"});
  tree.insert({2, "2"});
  tree.insert({3, "3"});
  tree.insert({4, "4"});
  std::ostringstream out1;
  printTree(out1, tree);
  BOOST_TEST(out1.str() == "1234");
  finaev::AVLtree< int, std::string > treeCopy(tree);
  tree.insert({5, "5"});
  std::ostringstream out2;
  printTree(out2, treeCopy);
  BOOST_TEST(out2.str() == "12345");
  finaev::AVLtree< int, std::string > treeMove(std::move(tree));
  std::ostringstream out3;
  printTree(out3, treeMove);
  BOOST_TEST(out3.str() == "1234");
  BOOST_TEST(tree.empty());
}

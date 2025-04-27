#include <boost/test/unit_test.hpp>
#include <string>
#include <sstream>
#include "tree.hpp"

namespace
{
 template< typename Key, typename Value, typename Cmp >
  void printTree(std::ostream & out, const maslov::BiTree< Key, Value, Cmp> & biTree)
  {
    out << biTree.cbegin()->first << ' ' << biTree.cbegin()->second;
    for (auto it = ++biTree.cbegin(); it != biTree.cend(); ++it)
    {
      out << ' ' << it->first << ' ' << it->second;
    }
  }
}

BOOST_AUTO_TEST_CASE(emptyTree)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  BOOST_TEST(tree.empty());
  bool check = tree.cbegin() == tree.cend();
  BOOST_TEST(check);
}

BOOST_AUTO_TEST_CASE(singleElement)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  std::ostringstream out;
  printTree(out, tree);
  BOOST_TEST(out.str() == "1 first");
}

BOOST_AUTO_TEST_CASE(moreElements)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(2, "second");
  tree.push(1, "first");
  tree.push(3, "third");
  tree.push(4, "fourth");
  tree.push(5, "fifth");
  tree.push(6, "sixth");
  std::ostringstream out;
  printTree(out, tree);
  BOOST_TEST(out.str() == "1 first 2 second 3 third 4 fourth 5 fifth 6 sixth");
}

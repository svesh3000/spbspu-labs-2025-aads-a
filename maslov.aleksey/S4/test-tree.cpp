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

BOOST_AUTO_TEST_CASE(defaultConstructor)
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

BOOST_AUTO_TEST_CASE(get)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  tree.push(2, "second");
  tree.push(3, "third");
  BOOST_TEST(tree.get(3) == "third");
}

BOOST_AUTO_TEST_CASE(pop)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  tree.push(2, "second");
  tree.push(3, "third");
  BOOST_TEST(tree.pop(2) == "second");
  std::ostringstream out;
  printTree(out, tree);
  BOOST_TEST(out.str() == "1 first 3 third");
}

BOOST_AUTO_TEST_CASE(copyConstructor)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  tree.push(2, "second");
  tree.push(3, "third");
  maslov::BiTree< int, std::string, std::less< int > > copy(tree);
  std::ostringstream out;
  printTree(out, copy);
  BOOST_TEST(out.str() == "1 first 2 second 3 third");
  tree.pop(2);
  BOOST_TEST(copy.size() == 3);
  BOOST_TEST(tree.size() == 2);
}

BOOST_AUTO_TEST_CASE(moveConstructor)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  tree.push(2, "second");
  tree.push(3, "third");
  maslov::BiTree< int, std::string, std::less< int > > moved(std::move(tree));
  std::ostringstream out;
  printTree(out, moved);
  BOOST_TEST(out.str() == "1 first 2 second 3 third");
  BOOST_TEST(tree.empty());
}

BOOST_AUTO_TEST_CASE(copyOperator)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  tree.push(2, "second");
  tree.push(3, "third");
  maslov::BiTree< int, std::string, std::less< int > > copy;
  copy = tree;
  std::ostringstream out1;
  printTree(out1, tree);
  std::ostringstream out2;
  printTree(out2, copy);
  BOOST_TEST(out1.str() == out2.str());
}

BOOST_AUTO_TEST_CASE(moveOperator)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  tree.push(2, "second");
  tree.push(3, "third");
  maslov::BiTree< int, std::string, std::less< int > > moved;
  moved = std::move(tree);
  std::ostringstream out;
  printTree(out, moved);
  BOOST_TEST(out.str() == "1 first 2 second 3 third");
  BOOST_TEST(tree.empty());
}

BOOST_AUTO_TEST_CASE(find)
{
  maslov::BiTree< int, std::string, std::less< int > > tree;
  tree.push(1, "first");
  tree.push(2, "second");
  tree.push(3, "third");
  auto it1 = tree.find(1);
  BOOST_TEST(it1->second == "first");
  auto it2 = tree.find(4);
  bool check = (it2 == tree.end());
  BOOST_TEST(check);
}

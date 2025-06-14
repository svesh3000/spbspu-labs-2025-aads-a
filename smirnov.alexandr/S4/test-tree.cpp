#include <boost/test/unit_test.hpp>
#include <string>
#include "avlTree.hpp"

BOOST_AUTO_TEST_CASE(DefaultConstructorTest)
{
  smirnov::AvlTree< int, std::string > tree;
  BOOST_TEST(tree.empty());
  BOOST_TEST(tree.size() == 0);
}

BOOST_AUTO_TEST_CASE(InsertAndSizeTest)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  BOOST_TEST(!tree.empty());
  BOOST_TEST(tree.size() == 1);
}

BOOST_AUTO_TEST_CASE(FindExistingElementTest)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  auto it = tree.find(1);
  BOOST_TEST(it != tree.cend());
}

BOOST_AUTO_TEST_CASE(FindNonExistingElementTest)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  auto it = tree.find(2);
  BOOST_TEST(it == tree.cend());
}

BOOST_AUTO_TEST_CASE(CopyConstructorTest)
{
  smirnov::AvlTree< int, std::string > tree1;
  tree1[1] = "one";
  smirnov::AvlTree< int, std::string > tree2(tree1);
  BOOST_TEST(tree2.size() == 1);
  BOOST_TEST(tree2.find(1) != tree2.cend());
}

BOOST_AUTO_TEST_CASE(MoveConstructorTest)
{
  smirnov::AvlTree< int, std::string > tree1;
  tree1[1] = "one";
  smirnov::AvlTree< int, std::string > tree2(std::move(tree1));
  BOOST_TEST(tree2.size() == 1);
  BOOST_TEST(tree1.empty());
}

BOOST_AUTO_TEST_CASE(ClearTest)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  tree.clear();
  BOOST_TEST(tree.empty());
  BOOST_TEST(tree.size() == 0);
}

BOOST_AUTO_TEST_CASE(BalanceTest)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  tree[2] = "two";
  tree[3] = "three";
  BOOST_TEST(tree.size() == 3);
  BOOST_TEST(tree.find(1) != tree.cend());
  BOOST_TEST(tree.find(2) != tree.cend());
  BOOST_TEST(tree.find(3) != tree.cend());
}

BOOST_AUTO_TEST_CASE(IteratorTest)
{
  smirnov::AvlTree< int, std::string > tree;
  tree[1] = "one";
  tree[2] = "two";
  int count = 0;
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    count++;
  }
  BOOST_TEST(count == 2);
}

#include <boost/test/unit_test.hpp>
#include <string>
#include "binary_tree.hpp"

BOOST_AUTO_TEST_CASE(test_true)
{
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(defaultconstructor_insert)
{
  abramov::BinarySearchTree< int, std::string > tree;
  tree.insert(10, "a");
  tree.insert(8, "b");
  auto it = tree.find(8);
  BOOST_TEST(it->second == "b");
}

BOOST_AUTO_TEST_CASE(begin)
{
  abramov::BinarySearchTree< int, std::string > tree;
  tree.insert(5, "a");
  tree.insert(1, "b");
  auto it = tree.begin();
  BOOST_TEST(it->second == "b");
}

BOOST_AUTO_TEST_CASE(cbegin)
{
  abramov::BinarySearchTree< int, std::string > tree;
  tree.insert(1, "a");
  tree.insert(5, "b");
  auto it = tree.cbegin();
  BOOST_TEST(it->second == "a");
}

BOOST_AUTO_TEST_CASE(find)
{
  abramov::BinarySearchTree< int, std::string > tree;
  tree.insert(10, "a");
  tree.insert(3, "b");
  tree.insert(12, "c");
  tree.insert(14, "d");
  auto it = tree.find(10);
  BOOST_TEST(it->second == "a");
  it = tree.find(3);
  BOOST_TEST(it->second == "b");
  it = tree.find(12);
  BOOST_TEST(it->second == "c");
  it = tree.find(14);
  BOOST_TEST(it->second == "d");
}

BOOST_AUTO_TEST_CASE(cfind)
{
  abramov::BinarySearchTree< int, std::string > tree;
  tree.insert(12, "a");
  tree.insert(9, "b");
  tree.insert(8, "c");
  tree.insert(7, "d");
  auto it = tree.find(12);
  BOOST_TEST(it->second == "a");
  it = tree.find(9);
  BOOST_TEST(it->second == "b");
  it = tree.find(8);
  BOOST_TEST(it->second == "c");
  it = tree.find(7);
  BOOST_TEST(it->second == "d");
}

BOOST_AUTO_TEST_CASE(count)
{
  abramov::BinarySearchTree< int, std::string > tree;
  tree.insert(12, "a");
  BOOST_TEST(tree.count(10) == 0);
  tree.insert(10, "b");
  BOOST_TEST(tree.count(10) == 1);
}

BOOST_AUTO_TEST_CASE(size)
{
  abramov::BinarySearchTree< int, std::string > tree;
  BOOST_TEST(tree.size() == 0);
  tree.insert(12, "a");
  BOOST_TEST(tree.size() == 1);
  tree.insert(14, "b");
  BOOST_TEST(tree.size() == 2);
}

BOOST_AUTO_TEST_CASE(empty)
{
  abramov::BinarySearchTree< int, std::string > tree;
  BOOST_TEST(tree.empty());
  tree.insert(10, "a");
  BOOST_TEST(!tree.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  abramov::BinarySearchTree< int, std::string > tree1;
  tree1.insert(4, "a");
  tree1.insert(2, "b");
  abramov::BinarySearchTree< int, std::string > tree2;
  tree2.insert(5, "c");
  tree2.insert(1, "d");
  tree1.swap(tree2);
  auto it1 = tree1.begin();
  auto it2 = tree2.begin();
  BOOST_TEST(it1->second == "d");
  BOOST_TEST(it2->second == "b");
}

BOOST_AUTO_TEST_CASE(clear)
{
  abramov::BinarySearchTree< int, std::string > tree;
  tree.insert(6, "a");
  tree.insert(3, "b");
  tree.clear();
  BOOST_TEST(tree.empty());
}

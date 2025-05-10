#include <boost/test/unit_test.hpp>
#include "two-three-tree.h"

BOOST_AUTO_TEST_CASE(operator_squared)
{
  savintsev::TwoThreeTree< int, int > map;
  map.insert({1, 10});
  BOOST_CHECK(map[1] == 10);
  map[1] = 111;
  map[2] = 20;
  map[10] = 100;
  map[5] = 50;
  map[8] = 80;
  map[18] = 180;
  map[20] = 200;
  map[0] = 11;
  map[-1] = -10;
  map[6] = 60;
  map[7] = 70;
  BOOST_CHECK(map[1] == 111);
  BOOST_CHECK(map[2] == 20);
  BOOST_CHECK(map[10] == 100);
  BOOST_CHECK(map[5] == 50);
  BOOST_CHECK(map[8] == 80);
  BOOST_CHECK(map[18] == 180);
  BOOST_CHECK(map[20] == 200);
  BOOST_CHECK(map[0] == 11);
  BOOST_CHECK(map[-1] == -10);
  BOOST_CHECK(map[6] == 60);
  BOOST_CHECK(map[7] == 70);
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  BOOST_CHECK(tree.empty());
  BOOST_CHECK(tree.size() == 0);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  savintsev::TwoThreeTree< int, std::string > original;
  original.insert({1, "one"});
  original.insert({2, "two"});

  savintsev::TwoThreeTree< int, std::string > copy(original);
  BOOST_CHECK(copy.size() == 2);
  BOOST_CHECK(copy.at(1) == "one");
  BOOST_CHECK(copy.at(2) == "two");
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  savintsev::TwoThreeTree< int, std::string > original;
  original.insert({1, "one"});
  original.insert({2, "two"});

  savintsev::TwoThreeTree< int, std::string > moved(std::move(original));
  BOOST_CHECK(moved.size() == 2);
  BOOST_CHECK(original.empty());
}

BOOST_AUTO_TEST_CASE(iterator_operations)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});
  tree.insert({3, "three"});

  auto it = tree.begin();
  BOOST_CHECK(it->first == 1);
  BOOST_CHECK(it->second == "one");

  ++it;
  BOOST_CHECK(it->first == 2);
  BOOST_CHECK(it->second == "two");

  ++it;
  BOOST_CHECK(it->first == 3);
  BOOST_CHECK(it->second == "three");

  ++it;
  BOOST_CHECK(it == tree.end());
}

BOOST_AUTO_TEST_CASE(clear_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});

  tree.clear();
  BOOST_CHECK(tree.empty());
  BOOST_CHECK(tree.size() == 0);
}

BOOST_AUTO_TEST_CASE(size_operations)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  BOOST_CHECK(tree.size() == 0);

  tree.insert({1, "one"});
  BOOST_CHECK(tree.size() == 1);

  tree.insert({2, "two"});
  BOOST_CHECK(tree.size() == 2);

  tree.erase(1);
  BOOST_CHECK(tree.size() == 1);
}

BOOST_AUTO_TEST_CASE(count_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});

  BOOST_CHECK(tree.count(1) == 1);
  BOOST_CHECK(tree.count(2) == 1);
  BOOST_CHECK(tree.count(3) == 0);
}

BOOST_AUTO_TEST_CASE(swap_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree1;
  tree1.insert({1, "one"});

  savintsev::TwoThreeTree< int, std::string > tree2;
  tree2.insert({2, "two"});

  tree1.swap(tree2);

  BOOST_CHECK(tree1.size() == 1);
  BOOST_CHECK(tree1.at(2) == "two");

  BOOST_CHECK(tree2.size() == 1);
  BOOST_CHECK(tree2.at(1) == "one");
}

BOOST_AUTO_TEST_CASE(find_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});

  auto it1 = tree.find(1);
  BOOST_CHECK(it1 != tree.end());
  BOOST_CHECK(it1->second == "one");

  auto it3 = tree.find(3);
  BOOST_CHECK(it3 == tree.end());
}

BOOST_AUTO_TEST_CASE(at_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree.insert({1, "one"});

  BOOST_CHECK(tree.at(1) == "one");
  BOOST_CHECK_THROW(tree.at(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(subscript_operator)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree[1] = "one";
  tree[2] = "two";

  BOOST_CHECK(tree[1] == "one");
  BOOST_CHECK(tree[2] == "two");
  BOOST_CHECK(tree.size() == 2);

  int key = 3;
  tree[std::move(key)] = "three";
  BOOST_CHECK(tree[3] == "three");
}

BOOST_AUTO_TEST_CASE(insert_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree;

  auto res1 = tree.insert({1, "one"});
  BOOST_CHECK(res1.second);
  BOOST_CHECK(res1.first->first == 1);

  auto res2 = tree.insert({1, "uno"});
  BOOST_CHECK(!res2.second);
  BOOST_CHECK(res2.first->first == 1);
  BOOST_CHECK(tree.at(1) == "one");
}

BOOST_AUTO_TEST_CASE(erase_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});
  tree.insert({3, "three"});

  //auto it = tree.find(2);
  //auto next_it = tree.erase(it);
  //BOOST_CHECK(next_it->first == 3);
  //BOOST_CHECK(tree.size() == 2);
  //BOOST_CHECK(tree.count(2) == 0);

  size_t erased = tree.erase(1);
  BOOST_CHECK(erased == 1);
  BOOST_CHECK(tree.size() == 2);

  erased = tree.erase(4);
  BOOST_CHECK(erased == 0);
}
/*
BOOST_AUTO_TEST_CASE(equal_range_operation)
{
  savintsev::TwoThreeTree< int, std::string > tree;
  tree.insert({1, "one"});
  tree.insert({2, "two"});
  tree.insert({4, "four"});

  auto range1 = tree.equal_range(2);
  //BOOST_CHECK(std::distance(range1.first, range1.second) == 1);
  BOOST_CHECK(range1.first->first == 2);

  auto range2 = tree.equal_range(3);
  BOOST_CHECK(range2.first == range2.second);
  BOOST_CHECK(range2.first->first == 4);
}
*/
BOOST_AUTO_TEST_CASE(const_methods)
{
  const savintsev::TwoThreeTree< int, std::string > tree = [](){
      savintsev::TwoThreeTree< int, std::string > t;
      t.insert({1, "one"});
      return t;
  }();

  BOOST_CHECK(tree.size() == 1);
  BOOST_CHECK(!tree.empty());

  auto it = tree.find(1);
  BOOST_CHECK(it != tree.end());
  BOOST_CHECK(it->second == "one");

  BOOST_CHECK(tree.at(1) == "one");
  BOOST_CHECK_THROW(tree.at(2), std::out_of_range);

  BOOST_CHECK(tree.count(1) == 1);
}


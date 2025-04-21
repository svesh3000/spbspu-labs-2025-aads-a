#include <boost/test/unit_test.hpp>
#include "tree.hpp"

using Tree = duhanina::Tree< int, std::string, std::less< int > >;

BOOST_AUTO_TEST_CASE(DefaultConstructorTest)
{
  Tree tree;
  BOOST_TEST(tree.empty());
}

BOOST_AUTO_TEST_CASE(CopyConstructorTest)
{
  Tree tree1;
  tree1.push(1, "one");
  tree1.push(2, "two");

  Tree tree2(tree1);
  BOOST_TEST(tree2.size() == 2);
}

BOOST_AUTO_TEST_CASE(MoveConstructorTest)
{
  Tree tree1;
  tree1.push(1, "one");
  tree1.push(2, "two");

  Tree tree2(std::move(tree1));
  BOOST_TEST(tree2.size() == 2);
  BOOST_TEST(tree1.empty());
}

BOOST_AUTO_TEST_CASE(AssignmentOperatorTest)
{
  Tree tree1;
  tree1.push(1, "one");
  tree1.push(2, "two");

  Tree tree2;
  tree2 = tree1;
  BOOST_TEST(tree2.size() == 2);
}

BOOST_AUTO_TEST_CASE(MoveAssignmentOperatorTest)
{
  Tree tree1;
  tree1.push(1, "one");
  tree1.push(2, "two");

  Tree tree2;
  tree2 = std::move(tree1);
  BOOST_TEST(tree2.size() == 2);
  BOOST_TEST(tree1.empty());
}

BOOST_AUTO_TEST_CASE(PushAndGetTest)
{
  Tree tree;
  tree.push(1, "one");
  tree.push(2, "two");

  BOOST_TEST(tree.get(2) == "two");
}

BOOST_AUTO_TEST_CASE(DropTest)
{
  Tree tree;
  tree.push(1, "one");
  tree.push(2, "two");

  BOOST_TEST(tree.drop(1) == "one");
  BOOST_TEST(tree.size() == 1);
}

BOOST_AUTO_TEST_CASE(SizeAndEmptyTest)
{
  Tree tree;
  BOOST_TEST(tree.empty());

  tree.push(1, "one");
  BOOST_TEST(tree.size() == 1);
}

BOOST_AUTO_TEST_CASE(ClearTest)
{
  Tree tree;
  tree.push(1, "one");
  tree.push(2, "two");

  tree.clear();
  BOOST_TEST(tree.empty());
}

BOOST_AUTO_TEST_CASE(SwapTest)
{
  Tree tree1;
  tree1.push(1, "one");
  Tree tree2;
  tree2.push(2, "two");

  tree1.swap(tree2);
  BOOST_TEST(tree1.get(2) == "two");
  BOOST_TEST(tree2.get(1) == "one");
}

BOOST_AUTO_TEST_CASE(InsertTest)
{
  Tree tree;
  tree.insert(std::make_pair(2, "two"));

  BOOST_TEST(tree.size() == 1);
  BOOST_TEST(tree.get(2) == "two");
}

BOOST_AUTO_TEST_CASE(EraseTest)
{
  Tree tree;
  tree.push(1, "one");
  tree.push(2, "two");
  tree.push(3, "three");

  auto it = tree.find(2);
  tree.erase(it);
  BOOST_TEST(tree.size() == 2);
  BOOST_TEST(tree.find(2) == tree.end());

  BOOST_TEST(tree.erase(3) == 1);
  BOOST_TEST(tree.size() == 1);

  tree.erase(tree.begin(), tree.end());
  BOOST_TEST(tree.empty());
}

BOOST_AUTO_TEST_CASE(AtAndOperatorTest)
{
  Tree tree;
  tree.push(1, "one");

  BOOST_TEST(tree.at(1) == "one");

  tree[2] = "two";
  BOOST_TEST(tree[2] == "two");

  tree[std::move(3)] = "three";
  BOOST_TEST(tree[3] == "three");
}

BOOST_AUTO_TEST_CASE(CountTest)
{
  Tree tree;
  tree.push(1, "one");

  BOOST_TEST(tree.count(1) == 1);
  BOOST_TEST(tree.count(2) == 0);
}

BOOST_AUTO_TEST_CASE(FindTest)
{
  Tree tree;
  tree.push(1, "one");

  BOOST_TEST(tree.find(1) != tree.end());
  BOOST_TEST(tree.find(2) == tree.end());
}

BOOST_AUTO_TEST_CASE(RangeTest)
{
  Tree tree;
  tree.push(1, "one");
  tree.push(2, "two");
  tree.push(3, "three");

  auto range = tree.equal_range(2);
  BOOST_TEST(range.first->data.first == 2);
  BOOST_TEST(range.second->data.first == 3);

  auto lb = tree.lower_bound(2);
  BOOST_TEST(lb->data.first == 2);

  auto ub = tree.upper_bound(2);
  BOOST_TEST(ub->data.first == 3);
}

BOOST_AUTO_TEST_CASE(RemoveNonexistentTest)
{
  Tree tree;
  tree.push(1, "one");
  BOOST_TEST(tree.erase(2) == 0);
  BOOST_TEST(tree.size() == 1);
}

BOOST_AUTO_TEST_CASE(CopyEmptyTreeTest)
{
  Tree tree1;
  Tree tree2(tree1);
  BOOST_TEST(tree2.empty());
}

BOOST_AUTO_TEST_CASE(MoveEmptyTreeTest)
{
  Tree tree1;
  Tree tree2(std::move(tree1));
  BOOST_TEST(tree2.empty());
  BOOST_TEST(tree1.empty());
}

BOOST_AUTO_TEST_CASE(ClearEmptyTreeTest)
{
  Tree tree;
  tree.clear();
  BOOST_TEST(tree.empty());
}

BOOST_AUTO_TEST_CASE(FindInEmptyTreeTest)
{
  Tree tree;
  BOOST_TEST(tree.find(1) == tree.end());
}

BOOST_AUTO_TEST_CASE(InsertDuplicateTest)
{
  Tree tree;
  tree.push(1, "one");
  tree.push(1, "new_one");
  BOOST_TEST(tree.size() == 1);
  BOOST_TEST(tree.get(1) == "new_one");
}

BOOST_AUTO_TEST_CASE(RotateTest)
{
  Tree tree;
  tree.push(3, "three");
  tree.push(2, "two");
  tree.push(1, "one");
  BOOST_TEST(tree.getRoot()->data.first == 2);

  Tree tree1;
  tree1.push(1, "one");
  tree1.push(2, "two");
  tree1.push(3, "three");
  BOOST_TEST(tree1.getRoot()->data.first == 2);
}

#include <boost/test/unit_test.hpp>
#include <functional>
#include <string>
#include <limits>
#include <tree.hpp>
#include "KeyValue.hpp"

using namespace duhanina;

namespace
{
  Tree< long long, std::string, std::less< long long > > create_test_tree()
  {
    Tree< long long, std::string, std::less< long long > > tree;
    tree.insert({ 5, "five" });
    tree.insert({ 3, "three" });
    tree.insert({ 7, "seven" });
    tree.insert({ 2, "two" });
    tree.insert({ 4, "four" });
    tree.insert({ 6, "six" });
    tree.insert({ 8, "eight" });
    return tree;
  }

  Tree< long long, std::string, std::less< long long > > create_overflow_tree()
  {
    Tree< long long, std::string, std::less< long long > > tree;
    tree.insert({ std::numeric_limits< long long >::max(), "max" });
    tree.insert({ 1, "one" });
    return tree;
  }

  Tree< long long, std::string, std::less< long long > > create_underflow_tree()
  {
    Tree< long long, std::string, std::less< long long > > tree;
    tree.insert({ std::numeric_limits< long long >::min(), "min" });
    tree.insert({ -1, "minus one" });
    return tree;
  }
}

BOOST_AUTO_TEST_CASE(LNRTraverseTest)
{
  auto tree = create_test_tree();

  ValueCollector vc;
  tree.traverse_lnr(vc);
  BOOST_TEST(vc.result == "two three four five six seven eight");

  KeySum ks;
  tree.traverse_lnr(ks);
  BOOST_TEST(ks.result == 35);

  const auto& constTree = tree;
  ValueCollector vcConst;
  constTree.traverse_lnr(vcConst);
  BOOST_TEST(vcConst.result == "two three four five six seven eight");
}

BOOST_AUTO_TEST_CASE(RNLTraverseTest)
{
  auto tree = create_test_tree();

  ValueCollector vc;
  tree.traverse_rnl(vc);
  BOOST_TEST(vc.result == "eight seven six five four three two");

  KeySum ks;
  tree.traverse_rnl(ks);
  BOOST_TEST(ks.result == 35);

  const auto& constTree = tree;
  ValueCollector vcConst;
  constTree.traverse_rnl(vcConst);
  BOOST_TEST(vcConst.result == "eight seven six five four three two");
}

BOOST_AUTO_TEST_CASE(BreadthTraverseTest)
{
  auto tree = create_test_tree();

  ValueCollector vc;
  tree.traverse_breadth(vc);
  BOOST_TEST(vc.result == "five three seven two four six eight");

  KeySum ks;
  tree.traverse_breadth(ks);
  BOOST_TEST(ks.result == 35);

  const auto& constTree = tree;
  ValueCollector vcConst;
  constTree.traverse_breadth(vcConst);
  BOOST_TEST(vcConst.result == "five three seven two four six eight");
}

BOOST_AUTO_TEST_CASE(EmptyTreeTraverseTest)
{
  Tree< long long, std::string, std::less< long long > > emptyTree;

  ValueCollector vc;
  emptyTree.traverse_lnr(vc);
  BOOST_TEST(vc.result.empty());

  KeySum ks;
  emptyTree.traverse_lnr(ks);
  BOOST_TEST(ks.result == 0);
}

BOOST_AUTO_TEST_CASE(KeySumOverflowThrowsTest)
{
  auto tree = create_overflow_tree();
  KeySum ks;
  bool exceptionThrown = false;
  try
  {
    tree.traverse_lnr(ks);
  }
  catch (...)
  {
    exceptionThrown = true;
  }
  BOOST_TEST(exceptionThrown);

  auto tree1 = create_underflow_tree();
  KeySum ks1;
  bool exceptionThrown1 = false;
  try
  {
    tree1.traverse_lnr(ks1);
  }
  catch (...)
  {
    exceptionThrown1 = true;
  }
  BOOST_TEST(exceptionThrown1);
}

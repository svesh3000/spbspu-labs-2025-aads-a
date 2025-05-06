#include <boost/test/unit_test.hpp>
#include "two-three-tree.h"

using namespace savintsev;

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
  AVLTree< int, int > tree;
  BOOST_CHECK(tree.empty());
  BOOST_CHECK_EQUAL(tree.size(), 0);
}

BOOST_AUTO_TEST_CASE(InitializerListConstructor)
{
  AVLTree< int, int > tree{{1, 10}, {2, 20}, {3, 30}};
  BOOST_CHECK_EQUAL(tree.size(), 3);
  BOOST_CHECK_EQUAL(tree[1], 10);
  BOOST_CHECK_EQUAL(tree[2], 20);
  BOOST_CHECK_EQUAL(tree[3], 30);
}

BOOST_AUTO_TEST_CASE(InsertSingle)
{
  AVLTree< int, int > tree;
  auto result = tree.insert({5, 50});
  BOOST_CHECK(result.second);
  BOOST_CHECK_EQUAL(tree[5], 50);
}

BOOST_AUTO_TEST_CASE(InsertDuplicate)
{
  AVLTree< int, int > tree;
  tree.insert({1, 10});
  auto result = tree.insert({1, 20});
  BOOST_CHECK(!result.second);
  BOOST_CHECK_EQUAL(tree[1], 20);
}

BOOST_AUTO_TEST_CASE(InsertRange)
{
  AVLTree< int, int > tree;
  std::vector<std::pair< int, int >> values{{1, 1}, {2, 4}, {3, 9}};
  tree.insert(values.begin(), values.end());
  BOOST_CHECK_EQUAL(tree.size(), 3);
  BOOST_CHECK_EQUAL(tree[2], 4);
}

BOOST_AUTO_TEST_CASE(OperatorSquareBrackets)
{
  AVLTree< int, int > tree;
  tree[10] = 100;
  BOOST_CHECK_EQUAL(tree[10], 100);
  tree[10] = 200;
  BOOST_CHECK_EQUAL(tree[10], 200);
}

BOOST_AUTO_TEST_CASE(Clear)
{
  AVLTree< int, int > tree{{1, 2}, {3, 4}};
  tree.clear();
  BOOST_CHECK(tree.empty());
  BOOST_CHECK_EQUAL(tree.size(), 0);
}

BOOST_AUTO_TEST_CASE(Swap)
{
  AVLTree< int, int > a{{1, 2}, {2, 4}};
  AVLTree< int, int > b{{5, 6}};
  a.swap(b);
  BOOST_CHECK_EQUAL(a.size(), 1);
  BOOST_CHECK_EQUAL(a[5], 6);
  BOOST_CHECK_EQUAL(b[2], 4);
}

BOOST_AUTO_TEST_CASE(Emplace)
{
  AVLTree< int, int > tree;
  auto result = tree.emplace(42, 1000);
  BOOST_CHECK(result.second);
  BOOST_CHECK_EQUAL(tree[42], 1000);
}

BOOST_AUTO_TEST_CASE(EmplaceHint)
{
  AVLTree< int, int > tree;
  auto it = tree.emplace_hint(tree.begin(), 33, 333);
  BOOST_CHECK_EQUAL(it->first, 33);
  BOOST_CHECK_EQUAL(it->second, 333);
}

BOOST_AUTO_TEST_CASE(EraserByKey)
{
  AVLTree< int, int > tree{{1, 1}, {2, 2}, {3, 3}};
  BOOST_CHECK_EQUAL(tree.erase(2), 1);
  BOOST_CHECK_EQUAL(tree.count(2), 0);
  BOOST_CHECK_EQUAL(tree.size(), 2);
}

BOOST_AUTO_TEST_CASE(EraserByIterator)
{
  AVLTree< int, int > tree{{1, 1}, {2, 2}};
  auto it = tree.find(1);
  it = tree.erase(it);
  BOOST_CHECK_EQUAL(tree.count(1), 0);
  BOOST_CHECK_EQUAL(tree.size(), 1);
  BOOST_CHECK_EQUAL(it->first, 2);
}

BOOST_AUTO_TEST_CASE(FindAndCount)
{
  AVLTree< int, int > tree;
  tree.insert({10, 100});
  BOOST_CHECK(tree.find(10) != tree.end());
  BOOST_CHECK_EQUAL(tree.count(10), 1);
  BOOST_CHECK_EQUAL(tree.count(999), 0);
}

BOOST_AUTO_TEST_CASE(EqualRangeTest)
{
  AVLTree< int, int > tree{{1, 10}, {2, 20}, {3, 30}};
  auto range = tree.equal_range(2);
  BOOST_CHECK_EQUAL(range.first->first, 2);
  BOOST_CHECK(range.second == ++range.first);
}

BOOST_AUTO_TEST_CASE(LowerAndUpperBound)
{
  AVLTree< int, int > tree{{1, 10}, {3, 30}, {5, 50}};
  BOOST_CHECK_EQUAL(tree.lower_bound(2)->first, 3);
  BOOST_CHECK_EQUAL(tree.upper_bound(3)->first, 5);
}

BOOST_AUTO_TEST_CASE(IteratorTraversal)
{
  AVLTree< int, int > tree{{2, 20}, {1, 10}, {3, 30}};

  std::vector< int > keys;
  for (auto it = tree.begin(); it != tree.end(); ++it)
  {
    keys.push_back(it->first);
  }

  std::vector< int > expected_keys{1, 2, 3};

  BOOST_CHECK_EQUAL(keys.size(), expected_keys.size());

  for (size_t i = 0; i < keys.size(); ++i)
  {
    BOOST_CHECK_EQUAL(keys[i], expected_keys[i]);
  }
}

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "ConstIteratorFwd.hpp"
#include "FwdList.hpp"
#include "IteratorFwd.hpp"

// BOOST_AUTO_TEST_CASE(test_default_constructor)
// {
//   gavrilova::FwdList< int > list;
//   BOOST_TEST(list.empty());
//   BOOST_TEST(list.size() == 0);
// }

// BOOST_AUTO_TEST_CASE(test_initializer_list_constructor)
// {
//   gavrilova::FwdList< int > list{1, 2, 3};
//   BOOST_TEST(list.size() == 3);
//   BOOST_TEST(list.front() == 1);
// }

// BOOST_AUTO_TEST_CASE(test_front)
// {
//   gavrilova::FwdList< int > list{42};
//   BOOST_TEST(list.front() == 42);
//   BOOST_CHECK_THROW(gavrilova::FwdList< int >{}.front(), std::out_of_range);
// }

// BOOST_AUTO_TEST_CASE(test_push_pop_front)
// {
//   gavrilova::FwdList< int > list;
//   list.push_front(1);
//   list.push_front(2);
//   BOOST_TEST(list.front() == 2);
//   list.pop_front();
//   BOOST_TEST(list.front() == 1);
// }

// BOOST_AUTO_TEST_CASE(test_clear)
// {
//   gavrilova::FwdList< int > list{1, 2, 3};
//   list.clear();
//   BOOST_TEST(list.empty());
// }

// BOOST_AUTO_TEST_CASE(test_iterators)
// {
//   gavrilova::FwdList< int > list{1, 2, 3};
//   auto it = list.begin();
//   BOOST_TEST(*it == 1);
//   ++it;
//   BOOST_TEST(*it == 2);
//   BOOST_TEST((it != list.end()));
// }

// BOOST_AUTO_TEST_CASE(test_remove)
// {
//   gavrilova::FwdList< int > list{1, 2, 3, 2};
//   list.remove(2);
//   BOOST_TEST(list.size() == 2);
//   BOOST_TEST(*list.begin() == 1);
// }

// BOOST_AUTO_TEST_CASE(test_reverse)
// {
//   gavrilova::FwdList< int > list{1, 2, 3};
//   list.reverse();
//   auto it = list.begin();
//   BOOST_TEST(*it == 3);
//   ++it;
//   BOOST_TEST(*it == 2);
//   ++it;
//   BOOST_TEST(*it == 1);
// }

// BOOST_AUTO_TEST_CASE(test_assignment_operator)
// {
//   gavrilova::FwdList< int > list1{1, 2, 3};
//   gavrilova::FwdList< int > list2;
//   list2 = list1;
//   BOOST_TEST(list1.size() == list2.size());
//   BOOST_TEST(list1.front() == list2.front());
// }

// BOOST_AUTO_TEST_CASE(test_comparison_operators)
// {
//   gavrilova::FwdList< int > list1{1, 2};
//   gavrilova::FwdList< int > list2{1, 2, 3};
//   BOOST_TEST(list1 < list2);
//   BOOST_TEST(list1 != list2);
// }

// BOOST_AUTO_TEST_CASE(test_insert)
// {
//   gavrilova::FwdList< int > list{1, 3};
//   auto it = list.begin();
//   ++it;
//   list.insert(it, 2);
//   BOOST_TEST(list.size() == 3);
//   BOOST_TEST(*++list.begin() == 3);
//   BOOST_TEST(*it == 3);
//   BOOST_TEST(*++it == 2);
// }

// BOOST_AUTO_TEST_CASE(test_erase)
// {
//   gavrilova::FwdList< int > list{1, 2, 3};
//   auto it = list.begin();
//   list.erase(it);
//   BOOST_TEST(list.size() == 2);
//   BOOST_TEST(*++list.begin() == 3);
// }

// BOOST_AUTO_TEST_CASE(test_splice)
// {
//   gavrilova::FwdList< int > list1{1, 2};
//   gavrilova::FwdList< int > list2{3, 4, 5};
//   auto pos = list1.begin();
//   list1.splice(pos, list2);
//   BOOST_TEST(list1.size() == 5);
//   BOOST_TEST(list2.empty());
// }
// BOOST_AUTO_TEST_CASE(test_swap)
// {
//   gavrilova::FwdList< int > list1{1, 2};
//   gavrilova::FwdList< int > list2{3, 4, 5};
//   list1.swap(list2);
//   BOOST_TEST(list1.size() == 3);
//   BOOST_TEST(list2.size() == 2);
// }

BOOST_AUTO_TEST_CASE(TestIteratorForwardTraversal)
{
  gavrilova::TwoThreeTree< int, std::string > tree;
  tree.push(10, "ten");
  tree.push(5, "five");
  tree.push(15, "fifteen");

  std::vector< std::pair< int, std::string > > expected = {
      {5, "five"}, {10, "ten"}, {15, "fifteen"}};

  auto it = tree.begin();
  for (size_t i = 0; i < expected.size(); ++i, ++it) {
    BOOST_CHECK(it != tree.end());
    BOOST_TEST(it->first == expected[i].first);
    BOOST_TEST(it->second == expected[i].second);
  }
  BOOST_CHECK(it == tree.end());
}

BOOST_AUTO_TEST_CASE(TestIteratorBackwardTraversal)
{
  gavrilova::TwoThreeTree< int, std::string > tree;
  tree.push(10, "ten");
  tree.push(5, "five");
  tree.push(15, "fifteen");

  std::vector< std::pair< int, std::string > > expected = {
      {15, "fifteen"}, {10, "ten"}, {5, "five"}};

  auto it = tree.end();
  --it;
  for (size_t i = 0; i < expected.size(); ++i, --it) {
    BOOST_TEST(it->first == expected[i].first);
    BOOST_TEST(it->second == expected[i].second);
    if (i != expected.size() - 1) {
      BOOST_CHECK(it != tree.begin());
    }
  }
}

BOOST_AUTO_TEST_CASE(TestIteratorEquality)
{
  gavrilova::TwoThreeTree< int, std::string > tree;
  tree.push(10, "ten");
  tree.push(20, "twenty");

  auto it1 = tree.begin();
  auto it2 = tree.begin();

  BOOST_CHECK(it1 == it2);
  ++it1;
  BOOST_CHECK(it1 != it2);
}

BOOST_AUTO_TEST_CASE(TestIteratorToEnd)
{
  gavrilova::TwoThreeTree< int, std::string > tree;
  tree.push(1, "a");
  tree.push(2, "b");

  auto it = tree.begin();
  while (it != tree.end()) {
    ++it;
  }

  BOOST_CHECK(it == tree.end());
}

BOOST_AUTO_TEST_CASE(TestIteratorDereference)
{
  gavrilova::TwoThreeTree< int, std::string > tree;
  tree.push(42, "answer");

  auto it = tree.begin();
  BOOST_CHECK(it != tree.end());
  BOOST_TEST((*it).first == 42);
  BOOST_TEST((*it).second == "answer");
  BOOST_TEST(it->first == 42);
  BOOST_TEST(it->second == "answer");
}

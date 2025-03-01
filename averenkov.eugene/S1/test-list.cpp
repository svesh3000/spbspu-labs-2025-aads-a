#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "list.hpp"

using IntList = averenkov::List< int >;

BOOST_AUTO_TEST_CASE(TestDefaultConstructor)
{
  IntList list;
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(TestPushFront)
{
  IntList list;
  list.push_front(10);
  BOOST_CHECK_EQUAL(list.front(), 10);
  BOOST_CHECK_EQUAL(list.size(), 1);
}

BOOST_AUTO_TEST_CASE(TestPushBack)
{
  IntList list;
  list.push_back(20);
  BOOST_CHECK_EQUAL(list.back(), 20);
  BOOST_CHECK_EQUAL(list.size(), 1);
}

BOOST_AUTO_TEST_CASE(TestPopFront)
{
  IntList list;
  list.push_front(30);
  list.pop_front();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(TestPopBack)
{
  IntList list;
  list.push_back(40);
  list.pop_back();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(TestCopyConstructor)
{
  IntList list1;
  list1.push_back(50);
  IntList list2 = list1;
  BOOST_CHECK_EQUAL(list2.size(), 1);
  BOOST_CHECK_EQUAL(list2.front(), 50);
}

BOOST_AUTO_TEST_CASE(TestMoveConstructor)
{
  IntList list1;
  list1.push_back(60);
  IntList list2 = std::move(list1);
  BOOST_CHECK_EQUAL(list2.size(), 1);
  BOOST_CHECK_EQUAL(list2.front(), 60);
  BOOST_CHECK(list1.empty());
}

BOOST_AUTO_TEST_CASE(TestAssign)
{
  IntList list;
  list.assign(3, 70);
  BOOST_CHECK_EQUAL(list.size(), 3);
  BOOST_CHECK_EQUAL(list.front(), 70);
  BOOST_CHECK_EQUAL(list.back(), 70);
}

BOOST_AUTO_TEST_CASE(TestRemove)
{
  IntList list;
  list.push_back(80);
  list.push_back(90);
  list.remove(80);
  BOOST_CHECK_EQUAL(list.size(), 1);
  BOOST_CHECK_EQUAL(list.front(), 90);
}

BOOST_AUTO_TEST_CASE(TestRemoveIf)
{
  IntList list;
  list.push_back(10);
  list.push_back(15);
  list.push_back(20);
  list.removeIf([](int val) { return val % 2 == 0; });
  BOOST_CHECK_EQUAL(list.size(), 1);
  BOOST_CHECK_EQUAL(list.front(), 15);
}

BOOST_AUTO_TEST_CASE(TestSplice)
{
  IntList list1, list2;
  list1.push_back(1);
  list1.push_back(2);
  list2.push_back(3);
  list2.push_back(4);
  list1.splice(list1.end(), list2);
  BOOST_CHECK_EQUAL(list1.size(), 4);
  BOOST_CHECK_EQUAL(list1.back(), 4);
  BOOST_CHECK(list2.empty());
}

BOOST_AUTO_TEST_CASE(TestSwap)
{
  IntList list1, list2;
  list1.push_back(100);
  list2.push_back(200);
  list1.swap(list2);
  BOOST_CHECK_EQUAL(list1.front(), 200);
  BOOST_CHECK_EQUAL(list2.front(), 100);
}

BOOST_AUTO_TEST_CASE(TestClear)
{
  IntList list;
  list.push_back(300);
  list.push_back(400);
  list.clear();
  BOOST_CHECK(list.empty());
}

BOOST_AUTO_TEST_CASE(TestIterator)
{
  IntList list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  int sum = 0;
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    sum += *it;
  }
  BOOST_CHECK_EQUAL(sum, 6);
}

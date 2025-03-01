#define BOOST_TEST_MODULE ListTest
#include <boost/test/included/unit_test.hpp>
#include "list.hpp"

using inList = averenkov::List< int >;

BOOST_AUTO_TEST_CASE(TestDefaultConstructor)
{
  inList list;
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(TestPushFront)
{
  inList list;
  list.push_front(10);
  BOOST_CHECK(!list.empty());
  BOOST_CHECK_EQUAL(list.size(), 1);
  BOOST_CHECK_EQUAL(list.front(), 10);
}

BOOST_AUTO_TEST_CASE(TestPushBack)
{
  inList list;
  list.push_back(20);
  BOOST_CHECK(!list.empty());
  BOOST_CHECK_EQUAL(list.size(), 1);
  BOOST_CHECK_EQUAL(list.back(), 20);
}

BOOST_AUTO_TEST_CASE(TestPopFront)
{
  inList list;
  list.push_front(30);
  list.pop_front();
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(TestPopBack)
{
  inList list;
  list.push_back(40);
  list.pop_back();
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(TestCopyConstructor)
{
  inList list1;
  list1.push_back(50);
  inList list2(list1);
  BOOST_CHECK_EQUAL(list2.size(), 1);
  BOOST_CHECK_EQUAL(list2.front(), 50);
}

BOOST_AUTO_TEST_CASE(TestAssignment)
{
  inList list1;
  list1.push_back(60);
  inList list2;
  list2 = list1;
  BOOST_CHECK_EQUAL(list2.size(), 1);
  BOOST_CHECK_EQUAL(list2.front(), 60);
}

BOOST_AUTO_TEST_CASE(TestClear)
{
  inList list;
  list.push_back(70);
  list.push_back(80);
  list.clear();
  BOOST_CHECK(list.empty());
  BOOST_CHECK_EQUAL(list.size(), 0);
}

BOOST_AUTO_TEST_CASE(TestRemove)
{
  inList list;
  list.push_back(90);
  list.push_back(100);
  list.remove(90);
  BOOST_CHECK_EQUAL(list.size(), 1);
  BOOST_CHECK_EQUAL(list.front(), 100);
}

BOOST_AUTO_TEST_CASE(TestAssign)
{
  inList list;
  list.assign(3, 42);
  BOOST_CHECK_EQUAL(list.size(), 3);
  BOOST_CHECK_EQUAL(list.front(), 42);
  BOOST_CHECK_EQUAL(list.back(), 42);
}


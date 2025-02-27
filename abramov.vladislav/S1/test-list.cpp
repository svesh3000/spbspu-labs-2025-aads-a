#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_CASE(empty)
{
  abramov::List< int > list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(size)
{
  abramov::List< int > list;
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(front_pushFront)
{
  abramov::List< int > list;
  list.pushFront(0);
  BOOST_TEST(list.front() == 0);
  list.pushFront(1);
  BOOST_TEST(list.front() == 1);
}

BOOST_AUTO_TEST_CASE(back_pushBack)
{
  abramov::List< int > list;
  list.pushBack(0);
  BOOST_TEST(list.back() == 0);
  list.pushBack(1);
  BOOST_TEST(list.back() == 1);
}

BOOST_AUTO_TEST_CASE(popFront)
{
  abramov::List< int > list;
  list.pushFront(0);
  list.popFront();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(popBack)
{
  abramov::List< int > list;
  list.pushBack(0);
  list.popBack();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  abramov::List< int > list1;
  abramov::List< int > list2;
  list1.pushBack(1);
  list1.pushBack(2);
  list2.pushBack(3);
  list2.pushBack(4);
  list1.swap(list2);
  BOOST_TEST(list1.front() == 3);
  BOOST_TEST(list1.back() == 4);
  BOOST_TEST(list2.front() == 1);
  BOOST_TEST(list2.back() == 2);
}

BOOST_AUTO_TEST_CASE(clear)
{
  abramov::List< int > list;
  list.pushBack(1);
  list.pushBack(2);
  list.clear();
  BOOST_TEST(list.empty());
}

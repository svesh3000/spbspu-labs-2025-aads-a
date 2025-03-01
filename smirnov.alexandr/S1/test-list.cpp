#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_CASE(PushBackTest)
{
  smirnov::List< int > list;
  list.pushBack(10);
  BOOST_TEST(list.getSize() == 1);
  BOOST_TEST(*list.begin() == 10);
}

BOOST_AUTO_TEST_CASE(IsEmptyTest)
{
  smirnov::List< int > list;
  BOOST_TEST(list.isEmpty());
  list.pushBack(10);
  BOOST_TEST(!list.isEmpty());
}

BOOST_AUTO_TEST_CASE(GetSizeTest)
{
  smirnov::List< int > list;
  BOOST_TEST(list.getSize() == 0);
  list.pushBack(10);
  list.pushBack(20);
  BOOST_TEST(list.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(PopFrontTest)
{
  smirnov::List< int > list;
  list.pushBack(10);
  list.pushBack(20);
  list.popFront();
  BOOST_TEST(list.getSize() == 1);
  BOOST_TEST(*list.begin() == 20);
}

BOOST_AUTO_TEST_CASE(IteratorTest)
{
  smirnov::List< int > list;
  list.pushBack(10);
  list.pushBack(20);
  auto it = list.begin();
  BOOST_TEST(*it == 10);
  ++it;
  BOOST_TEST(*it == 20);
  ++it;
  BOOST_TEST(it == list.end());
}

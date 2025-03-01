#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_CASE(construction)
{
  aleksandrov::List< int > list;
}

BOOST_AUTO_TEST_CASE(begin)
{
  aleksandrov::List< double > list;
  list.pushFront(1.23);
  BOOST_TEST(*(list.begin()) == 1.23);
}

BOOST_AUTO_TEST_CASE(front)
{
  aleksandrov::List< char > list;
  list.pushFront('a');
  BOOST_TEST(list.front() == 'a');
}

BOOST_AUTO_TEST_CASE(empty)
{
  aleksandrov::List< char > list;
  BOOST_TEST(list.empty());
  list.pushFront('a');
  BOOST_TEST(!list.empty());
}

BOOST_AUTO_TEST_CASE(size)
{
  aleksandrov::List< double > list;
  BOOST_TEST(list.size() == 0);
  list.pushFront(3.14159);
  BOOST_TEST(list.size());
  list.pushFront(2.71828);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(pushFront)
{
  aleksandrov::List< float > list;
  list.pushFront(1.0);
  BOOST_TEST(list.front() == 1.0);
  list.pushFront(3.14);
  BOOST_TEST(list.front() == 3.14);
}

BOOST_AUTO_TEST_CASE(popFront)
{
  aleksandrov::List< int > list;
  list.popFront();
  list.pushFront(2025);
  list.popFront();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  aleksandrov::List< int > list1;
  list1.pushFront(1);
  list1.pushFront(2);
  aleksandrov::List< int > list2;
  list2.pushFront(3);
  auto it = list1.begin();
  list1.swap(list2);
  BOOST_TEST(list1.front() == 3);
  BOOST_TEST(*it == 1);
}

BOOST_AUTO_TEST_CASE(clear)
{
  aleksandrov::List< short > list;
  list.clear();
  list.clear();
  list.pushFront(-1);
  list.pushFront(-2);
  list.clear();
  BOOST_TEST(list.empty());
}


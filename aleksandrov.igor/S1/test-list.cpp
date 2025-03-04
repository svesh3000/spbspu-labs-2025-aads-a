#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_CASE(construction)
{
  aleksandrov::List< int > list;
}

BOOST_AUTO_TEST_CASE(begin_end)
{
  aleksandrov::List< int > list;
  list.pushBack(12);
  list.pushBack(34);
  list.pushBack(56);
  BOOST_TEST(*list.begin() == 12);
  BOOST_TEST(*list.end() == 56);
}

BOOST_AUTO_TEST_CASE(front_back)
{
  aleksandrov::List< char > list;
  list.pushFront('a');
  list.pushFront('b');
  list.pushFront('c');
  BOOST_TEST(list.front() == 'c');
  BOOST_TEST(list.back() == 'a');
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
  list.pushFront(1.0f);
  BOOST_TEST(list.front() == 1.0f);
  list.pushFront(3.14f);
  BOOST_TEST(list.front() == 3.14f);
}

BOOST_AUTO_TEST_CASE(pushBack)
{
  aleksandrov::List< float > list;
  list.pushBack(2.5f);
  BOOST_TEST(list.back() == 2.5f);
  list.pushBack(5.0f);
  BOOST_TEST(list.back() == 5.0f);
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
  list1.pushBack(1);
  list1.pushBack(2);
  aleksandrov::List< int > list2;
  list2.pushBack(3);
  list1.swap(list2);
  BOOST_TEST(list1.front() == 3);
  BOOST_TEST(list2.back() == 2);
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


#include <boost/test/tools/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <endian.h>
#include "constIterator.hpp"
#include "iterator.hpp"
#include "list.hpp"

using namespace kiselev;
BOOST_AUTO_TEST_SUITE(list)

BOOST_AUTO_TEST_CASE(empty)
{
  List< int > list;
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(size)
{
  List< int > list;
  const int i = 1;
  list.push_back(i);
  BOOST_TEST(list.size() == 1);
}

BOOST_AUTO_TEST_CASE(front_and_push_front)
{
  List< int > list;
  int i = 1;
  list.push_front(i);
  list.push_front(++i);
  BOOST_TEST(list.front() == i);
}

BOOST_AUTO_TEST_CASE(back_and_push_back)
{
  List< int > list;
  int i = 1;
  list.push_back(i);
  list.push_back(++i);
  BOOST_TEST(list.back() == i);
}

BOOST_AUTO_TEST_CASE(pop_back)
{
  List< int > list;
  int i = 1;
  list.push_back(i);
  list.push_back(++i);
  list.pop_back();
  BOOST_TEST(list.back() == --i);
  list.pop_back();
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(pop_front)
{
  List< int > list;
  int i = 1;
  list.push_front(i);
  list.push_back(++i);
  list.pop_front();
  BOOST_TEST(list.front() == i);
  list.pop_front();
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(clear)
{
  List< int > list;
  int i = 1;
  list.push_back(i);
  list.push_back(++i);
  list.push_front(i);
  list.clear();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  List< int > list;
  int i = 0;
  list.push_back(i);
  List< int > copyList(list);
  List< int > list2;
  list2.push_back(++i);
  list2.push_front(++i);
  list2.swap(list);
  BOOST_TEST(list2.size() == copyList.size());
}

BOOST_AUTO_TEST_CASE(erase_pos)
{
  List< int > list;
  for (size_t i = 0; i < 20; ++i)
  {
    list.push_back(i);
  }
  ConstIterator< int > begin = list.cbegin();
  Iterator< int > it = list.erase(begin);
  BOOST_CHECK(it == list.begin());
  ConstIterator< int > end = list.clast();
  it = list.erase(end);
  BOOST_CHECK(it == ++list.last());
  ConstIterator< int > iter = ++list.cbegin();
  it = list.erase(iter);
  BOOST_CHECK(*it == 3);
  begin = ++list.cbegin();
  end = list.cend();
  it = list.erase(begin, end);
  BOOST_CHECK(it == list.end());
}


BOOST_AUTO_TEST_SUITE_END()

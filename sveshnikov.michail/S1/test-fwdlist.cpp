#include <boost/test/unit_test.hpp>
#include "fwdlist-ring.hpp"

BOOST_AUTO_TEST_SUITE(constructors)
BOOST_AUTO_TEST_CASE(default_constructor)
{
  sveshnikov::FwdList< int > list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  sveshnikov::FwdList< int > list;
  sveshnikov::FwdList< int > list_copy = list;
  BOOST_TEST(list_copy.empty());
  list.push_back(1);
  sveshnikov::FwdList< int > list_copy2 = list;
  BOOST_TEST(list_copy2.front() == 1);
  list.push_back(2);
  sveshnikov::FwdList< int > list_copy3 = list;
  BOOST_TEST(list_copy3.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  sveshnikov::FwdList< int > list_copy = std::move(list);
  BOOST_TEST(list_copy.getSize() == 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(interface)
BOOST_AUTO_TEST_CASE(iterators)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  BOOST_TEST(*list.begin() == 1);
  BOOST_TEST(*list.cbegin() == 1);

  BOOST_TEST(*list.end() == 1);
  BOOST_TEST(*list.cend() == 1);

  BOOST_TEST(*list.before_begin() == 2);
  BOOST_TEST(*list.cbefore_begin() == 2);
}

BOOST_AUTO_TEST_CASE(ellement_access)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 2);
}

BOOST_AUTO_TEST_CASE(capacity)
{
  sveshnikov::FwdList< int > list;
  BOOST_TEST(list.getSize() == 0);
  BOOST_TEST(list.empty());
  list.push_back(1);
  BOOST_TEST(list.getSize() == 1);
  BOOST_TEST(!list.empty());
}

BOOST_AUTO_TEST_CASE(push)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  BOOST_TEST(list.getSize() == 1);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 1);
  list.push_front(2);
  list.push_back(3);
  BOOST_TEST(list.front() == 2);
  BOOST_TEST(*(++list.begin()) == 1);
  BOOST_TEST(list.back() == 3);

  int a = 4, b = 5;
  list.push_front(a);
  list.push_back(b);
  BOOST_TEST(list.front() == a);
  BOOST_TEST(list.back() == b);
}

BOOST_AUTO_TEST_CASE(pop)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  list.pop_back();
  BOOST_TEST(list.empty());
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.pop_back();
  list.pop_front();
  BOOST_TEST(list.front() == 2);
  BOOST_TEST(list.back() == 2);
}

BOOST_AUTO_TEST_CASE(swap)
{
  sveshnikov::FwdList< int > list1;
  list1.push_back(1);
  sveshnikov::FwdList< int > list2;
  list2.push_back(2);
  list1.swap(list2);
  BOOST_TEST(list1.front() == 2);
  BOOST_TEST(list2.front() == 1);
}

BOOST_AUTO_TEST_CASE(clear)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  list.clear();
  BOOST_TEST(list.empty());
}
BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>
#include <sstream>
#include "list.hpp"

using namespace tkach;

BOOST_AUTO_TEST_CASE(basic_contructor_test)
{
  List< int > list;
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(list_push_front_test)
{
  List< int > list;
  list.push_front(1);
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.push_front(2);
  BOOST_TEST(list.front() == 2);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(list_push_back_test)
{
  List< int > list;
  list.push_back(1);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.push_back(2);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(list_move_push_front_test)
{
  List< int > list;
  int a = 1;
  list.push_front(a);
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  int b = 2;
  list.push_front(b);
  auto it = list.begin();
  it++;
  BOOST_TEST(list.front() == 2);
  BOOST_TEST(*it == 1);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(list_move_push_back_test)
{
  List< int > list;
  int a = 1;
  list.push_back(a);
  auto it = list.begin();
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  a = 2;
  list.push_back(a);
  it++;
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(*it == 2);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(list_pop_front_test)
{
  List< int > list;
  list.push_back(1);
  list.push_back(2);
  list.pop_front();
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() = 2);
}

BOOST_AUTO_TEST_CASE(list_clear_test)
{
  List< int > lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.clear();
  BOOST_TEST(lst.empty() == true);
  BOOST_TEST(lst.size() == 0);
}

BOOST_AUTO_TEST_CASE(list_move_constructor_test)
{
  List< int > list1;
  list1.push_back(1);
  list1.push_back(2);
  List< int > list2(std::move(list1));
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list1.size() == 0);
}

BOOST_AUTO_TEST_CASE(list_copy_constructor_test)
{
  List< int > list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);
  List< int > list2(list1);
  auto it = list1.begin();
  BOOST_TEST(*(it++) == 1);
  BOOST_TEST(*(it++) == 2);
  BOOST_TEST(*(it++) == 3);
}

BOOST_AUTO_TEST_CASE(list_begin_end_test)
{
  List< int > list1;
  list1.push_back(1);
  list1.push_back(2);
  auto it1 = list1.begin();
  auto it2 = list1.end();
  BOOST_TEST(*it1 == 1);
  BOOST_TEST(*it2 == 1);
}


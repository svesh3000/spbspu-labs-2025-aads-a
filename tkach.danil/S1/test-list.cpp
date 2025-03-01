#include <boost/test/unit_test.hpp>
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
  list.pushFront(1);
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.pushFront(2);
  BOOST_TEST(list.front() == 2);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(list_push_back_test)
{
  List< int > list;
  list.pushBack(1);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.pushBack(2);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(list_move_push_front_test)
{
  List< int > list;
  int a = 1;
  list.pushFront(a);
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  int b = 2;
  list.pushFront(b);
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
  list.pushBack(a);
  auto it = list.begin();
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  a = 2;
  list.pushBack(a);
  it++;
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(*it == 2);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(list_pop_front_test)
{
  List< int > list;
  list.pushBack(1);
  list.pushBack(2);
  list.popFront();
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() = 2);
}

BOOST_AUTO_TEST_CASE(list_clear_test)
{
  List< int > lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.clear();
  BOOST_TEST(lst.empty() == true);
  BOOST_TEST(lst.size() == 0);
}

BOOST_AUTO_TEST_CASE(list_move_constructor_test)
{
  List< int > list1;
  list1.pushBack(1);
  list1.pushBack(2);
  List< int > list2(std::move(list1));
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list1.size() == 0);
}

BOOST_AUTO_TEST_CASE(list_copy_constructor_test)
{
  List< int > list1;
  list1.pushBack(1);
  list1.pushBack(2);
  list1.pushBack(3);
  List< int > list2(list1);
  auto it = list1.begin();
  BOOST_TEST(*(it++) == 1);
  BOOST_TEST(*(it++) == 2);
  BOOST_TEST(*(it++) == 3);
}

BOOST_AUTO_TEST_CASE(list_swap_test)
{
  List< int > list1;
  list1.pushBack(1);
  list1.pushBack(2);
  List< int > list2;
  list2.swap(list1);
  BOOST_TEST(list1.empty());
  auto it = list2.begin();
  BOOST_TEST(*it == 1);
  it++;
  BOOST_TEST(*it == 2);
}

BOOST_AUTO_TEST_CASE(list_fill_test)
{
  size_t count = 5;
  List< int > list(count, 54);
  BOOST_TEST(list.size() == 5);
  auto it = list.begin();
  for (size_t i = 0; i < count; ++i)
  {
    BOOST_TEST(*it == 54);
  }
}

BOOST_AUTO_TEST_CASE(list_begin_end_test)
{
  List< int > list1;
  list1.pushBack(1);
  list1.pushBack(2);
  auto it1 = list1.begin();
  auto it2 = list1.end();
  BOOST_TEST(*it1 == 1);
  BOOST_TEST(*it2 == 1);
}


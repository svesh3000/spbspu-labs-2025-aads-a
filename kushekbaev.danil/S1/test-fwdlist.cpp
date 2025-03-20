#include <boost/test/unit_test.hpp>
#include <sstream>
#include <string>
#include "fwdlist.hpp"

using list_t = kushekbaev::FwdList< int >;

std::string printList(list_t list)
{
  std::ostringstream out;
  for (auto it = list.begin(); it != list.end(); it++)
  {
    out << *it;
  }
  return out.str();
}

BOOST_AUTO_TEST_SUITE(list)

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  list_t list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(copyEmptyList)
{
  list_t list1;
  list_t list2(list1);
  BOOST_TEST(list2.empty());
}

BOOST_AUTO_TEST_CASE(copyListWithValues)
{
  list_t list1{ 1, 2, 3 };
  list_t list2(list1);
  BOOST_TEST(printList(list2) == "123");
}

BOOST_AUTO_TEST_CASE(moveConstructor)
{
  list_t list1({ 0, 1 });
  list_t list2(std::move(list1));
  BOOST_TEST(printList(list2) == "01");
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(beginEnd)
{
  list_t list({ 1, 2, 3 });
  auto it1 = list.begin();
  BOOST_TEST(*it1 == 1);
  ++it1;
  BOOST_TEST(*it1 == 2);
  ++it1;
  BOOST_TEST(*it1 == 3);
  ++it1;
  auto it2 = list.end();
  BOOST_TEST(*it1 == *it2);
}

BOOST_AUTO_TEST_CASE(front)
{
  list_t list({ 1, 2, 3 });
  BOOST_TEST(list.front() == 1);
}

BOOST_AUTO_TEST_CASE(back)
{
  list_t list({ 1, 2, 3 });
  BOOST_TEST(list.back() == 3);
}

BOOST_AUTO_TEST_CASE(pushfront)
{
  list_t list({ 1, 2, 3 });
  list.push_front(0);
  BOOST_TEST(printList(list) == "0123");
}

BOOST_AUTO_TEST_CASE(pushback)
{
  list_t list({ 1, 2, 3 });
  list.push_back(4);
  BOOST_TEST(printList(list) == "1234");
}

BOOST_AUTO_TEST_CASE(popfront)
{
  list_t list({ 0, 1, 2, 3 });
  list.pop_front();
  BOOST_TEST(printList(list) == "123");
}

BOOST_AUTO_TEST_CASE(popback)
{
  list_t list({ 0, 1, 2, 3 });
  list.pop_back();
  BOOST_TEST(printList(list) == "012");
}

BOOST_AUTO_TEST_CASE(clear)
{
  list_t list({ 1, 2, 3 });
  list.clear();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  list_t list1({ 1337 });
  list_t list2({ 1984 });
  list1.swap(list2);
  BOOST_TEST(printList(list1) == "1984");
  BOOST_TEST(printList(list2) == "1337");
}

BOOST_AUTO_TEST_CASE(size)
{
  list_t list({ 0, 1, 2, 3, 4, 5, 6 });
  BOOST_TEST(list.size() == 7);
}

BOOST_AUTO_TEST_CASE(empty)
{
  list_t list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_SUITE_END()

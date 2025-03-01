#include <boost/test/unit_test.hpp>
#include <iostream>
#include "list.hpp"

using FwdList = maslov::FwdList< int >;

BOOST_AUTO_TEST_SUITE(constructors)

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  FwdList list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(fillConstructor)
{
  FwdList list(4, 4);
  BOOST_TEST(list.size() == 4);
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    BOOST_TEST(*it == 4);
  }
}

BOOST_AUTO_TEST_CASE(copyConstructor)
{
  FwdList list1;
  list1.push_front(1);
  list1.push_front(2);
  FwdList list2 = list1;
  BOOST_TEST(list1 == list2);
  list2.push_front(3);
  BOOST_TEST(list1 != list2);
}

BOOST_AUTO_TEST_CASE(moveConstructor)
{
  FwdList list1;
  list1.push_front(1);
  list1.push_front(2);
  FwdList list3 = list1;
  FwdList list2 = std::move(list1);
  BOOST_TEST(list1.empty());
  BOOST_TEST(list2 == list3);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operators)

BOOST_AUTO_TEST_CASE(copyOperator)
{
  FwdList list1;
  list1.push_front(1);
  list1.push_front(2);
  FwdList list2;
  list2 = list1;
  BOOST_TEST(list2 == list1);
}

BOOST_AUTO_TEST_CASE(moveOperator)
{
  FwdList list1;
  list1.push_front(1);
  list1.push_front(2);
  FwdList list3 = list1;
  FwdList list2;
  list2 = std::move(list1);
  BOOST_TEST(list2 == list3);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(equalOperator)
{
  FwdList list1;
  list1.push_front(1);
  list1.push_front(2);
  FwdList list2;
  list2.push_front(1);
  list2.push_front(2);
  BOOST_TEST(list1 == list2);
  list1.push_front(3);
  BOOST_TEST(list1 != list2);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(modifiers)

BOOST_AUTO_TEST_CASE(pushFront)
{
  FwdList list;
  list.push_front(1);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.push_front(2);
  BOOST_TEST(list.size() == 2);
  BOOST_TEST(list.front() == 2);
}

BOOST_AUTO_TEST_CASE(popFront)
{
  FwdList list;
  list.push_front(1);
  list.push_front(2);
  list.pop_front();
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.pop_front();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  FwdList list1;
  list1.push_front(1);
  list1.push_front(2);
  FwdList list2;
  list2.push_front(3);
  list2.push_front(4);
  list2.push_front(5);
  FwdList tempList1 = list1;
  FwdList tempList2 = list2;
  list1.swap(list2);
  BOOST_TEST(list1 == tempList2);
  BOOST_TEST(list2 == tempList1);
}

BOOST_AUTO_TEST_CASE(clear)
{
  FwdList list;
  list.push_front(1);
  list.push_front(2);
  list.clear();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operations)

BOOST_AUTO_TEST_CASE(reverse)
{
  FwdList emptyList;
  emptyList.reverse();
  BOOST_TEST(emptyList.empty());
  FwdList listOneElement;
  listOneElement.push_front(1);
  listOneElement.reverse();
  BOOST_TEST(listOneElement.size() == 1);
  BOOST_TEST(listOneElement.front() == 1);
  FwdList list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.reverse();
  BOOST_TEST(list.size() == 3);
  auto it = list.begin();
  BOOST_TEST(*it++ == 1);
  BOOST_TEST(*it++ == 2);
  BOOST_TEST(*it++ == 3);
}

BOOST_AUTO_TEST_CASE(remove)
{}

BOOST_AUTO_TEST_CASE(removeIf)
{}

BOOST_AUTO_TEST_SUITE_END()

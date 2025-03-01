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
{}

BOOST_AUTO_TEST_CASE(popFront)
{}

BOOST_AUTO_TEST_CASE(swap)
{}

BOOST_AUTO_TEST_CASE(clear)
{}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operations)

BOOST_AUTO_TEST_CASE(reverse)
{}

BOOST_AUTO_TEST_CASE(remove)
{}

BOOST_AUTO_TEST_CASE(removeIf)
{}

BOOST_AUTO_TEST_SUITE_END()

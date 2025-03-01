#include <boost/test/unit_test.hpp>
#include <sstream>
#include "list.hpp"

using FwdList = maslov::FwdList< int >;

namespace
{
  std::ostream & printList(std::ostream & out, FwdList list)
  {
    for (auto it = list.begin(); it != list.end(); it++)
    {
      out << *it;
    }
    return out;
  }
  bool lessThanThree(const int & value)
  {
    return (value < 3);
  }
}

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
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "4444");
}

BOOST_AUTO_TEST_CASE(copyConstructor)
{
  FwdList list1;
  list1.pushFront(1);
  list1.pushFront(2);
  FwdList list2 = list1;
  BOOST_TEST(list1 == list2);
  list2.pushFront(3);
  BOOST_TEST(list1 != list2);
}

BOOST_AUTO_TEST_CASE(moveConstructor)
{
  FwdList list1;
  list1.pushFront(1);
  list1.pushFront(2);
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
  list1.pushFront(1);
  list1.pushFront(2);
  FwdList list2;
  list2 = list1;
  BOOST_TEST(list2 == list1);
}

BOOST_AUTO_TEST_CASE(moveOperator)
{
  FwdList list1;
  list1.pushFront(1);
  list1.pushFront(2);
  FwdList list3 = list1;
  FwdList list2;
  list2 = std::move(list1);
  BOOST_TEST(list2 == list3);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(equalOperator)
{
  FwdList list1;
  list1.pushFront(1);
  list1.pushFront(2);
  FwdList list2;
  list2.pushFront(1);
  list2.pushFront(2);
  BOOST_TEST(list1 == list2);
  list1.pushFront(3);
  BOOST_TEST(list1 != list2);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(modifiers)

BOOST_AUTO_TEST_CASE(pushFront)
{
  FwdList list;
  list.pushFront(1);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.pushFront(2);
  BOOST_TEST(list.size() == 2);
  BOOST_TEST(list.front() == 2);
}

BOOST_AUTO_TEST_CASE(popFront)
{
  FwdList list;
  list.pushFront(1);
  list.pushFront(2);
  list.popFront();
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.popFront();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  FwdList list1;
  list1.pushFront(1);
  list1.pushFront(2);
  FwdList list2;
  list2.pushFront(3);
  list2.pushFront(4);
  list2.pushFront(5);
  FwdList tempList1 = list1;
  FwdList tempList2 = list2;
  list1.swap(list2);
  BOOST_TEST(list1 == tempList2);
  BOOST_TEST(list2 == tempList1);
}

BOOST_AUTO_TEST_CASE(clear)
{
  FwdList list;
  list.pushFront(1);
  list.pushFront(2);
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
  listOneElement.pushFront(1);
  listOneElement.reverse();
  BOOST_TEST(listOneElement.size() == 1);
  BOOST_TEST(listOneElement.front() == 1);
  FwdList list;
  list.pushFront(1);
  list.pushFront(2);
  list.pushFront(3);
  list.reverse();
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "123");
}

BOOST_AUTO_TEST_CASE(remove)
{
  FwdList list;
  list.pushFront(1);
  list.pushFront(2);
  list.pushFront(5);
  list.pushFront(3);
  list.pushFront(5);
  list.pushFront(4);
  list.remove(5);
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "4321");

}

BOOST_AUTO_TEST_CASE(removeIf)
{
  FwdList list;
  list.pushFront(1);
  list.pushFront(3);
  list.pushFront(5);
  list.pushFront(2);
  list.removeIf(lessThanThree);
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "53");
}

BOOST_AUTO_TEST_SUITE_END()

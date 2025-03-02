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
  FwdList list1{1, 2};
  FwdList list2 = list1;
  BOOST_TEST(list1 == list2);
  list2.pushFront(3);
  BOOST_TEST(list1 != list2);
}

BOOST_AUTO_TEST_CASE(moveConstructor)
{
  FwdList list1{1, 2};
  FwdList list3 = list1;
  FwdList list2 = std::move(list1);
  BOOST_TEST(list1.empty());
  BOOST_TEST(list2 == list3);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operators)

BOOST_AUTO_TEST_CASE(copyOperator)
{
  FwdList list1{1, 2};
  FwdList list2;
  list2 = list1;
  BOOST_TEST(list2 == list1);
}

BOOST_AUTO_TEST_CASE(moveOperator)
{
  FwdList list1{1, 2};
  FwdList list3 = list1;
  FwdList list2;
  list2 = std::move(list1);
  BOOST_TEST(list2 == list3);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(equalOperator)
{
  FwdList list1{1, 2};
  FwdList list2{1, 2};
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
  FwdList list = {1, 2};
  list.popFront();
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 2);
  list.popFront();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  FwdList list1 = {1, 2};
  FwdList list2 = {3, 4, 5};
  FwdList tempList1 = list1;
  FwdList tempList2 = list2;
  list1.swap(list2);
  BOOST_TEST(list1 == tempList2);
  BOOST_TEST(list2 == tempList1);
}

BOOST_AUTO_TEST_CASE(clear)
{
  FwdList list{1, 2};
  list.clear();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(assignInitializer)
{
  FwdList list;
  list.pushFront(1);
  list.assign({2});
  std::ostringstream out1;
  printList(out1, list);
  BOOST_TEST(out1.str() == "2");

  list.assign({1, 2, 3});
  std::ostringstream out2;
  printList(out2, list);
  BOOST_TEST(out2.str() == "123");
}

BOOST_AUTO_TEST_CASE(assignRange)
{
  FwdList list({1, 2, 3});
  list.assign(list.begin(), list.end());
  std::ostringstream out1;
  printList(out1, list);
  BOOST_TEST(out1.str() == "123");

  list.assign({7, 8, 9});
  list.assign(list.cbegin(), list.cend());
  std::ostringstream out2;
  printList(out2, list);
  BOOST_TEST(out2.str() == "789");
}

BOOST_AUTO_TEST_CASE(assignFill)
{
  FwdList list;
  list.assign(3, 4);
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "444");
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
  FwdList list{1, 2, 3};
  list.reverse();
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "321");
}

BOOST_AUTO_TEST_CASE(remove)
{
  FwdList list{1, 2, 5, 3, 5, 4};
  list.remove(5);
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "1234");

}

BOOST_AUTO_TEST_CASE(removeIf)
{
  FwdList list{2, 5, 3, 1};
  list.removeIf(lessThanThree);
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "53");
}

BOOST_AUTO_TEST_CASE(SpliceAfter)
{
  FwdList list1{1, 2, 3};
  FwdList list2{4, 5, 6};
  list1.spliceAfter(list1.cbegin(), list2);
  std::ostringstream out1;
  printList(out1, list1);
  std::ostringstream out2;
  printList(out2, list2);
  BOOST_TEST(out1.str() == "145623");
  BOOST_TEST(out2.str() == "");
}

BOOST_AUTO_TEST_CASE(SpliceAfterPoint)
{
  FwdList list1{1, 2, 3};
  FwdList list2{4, 5, 6};
  auto it = ++list2.cbegin();
  list1.spliceAfter(list1.cbegin(), list2, it);
  std::ostringstream out1;
  printList(out1, list1);
  std::ostringstream out2;
  printList(out2, list2);
  BOOST_TEST(out1.str() == "1623");
  BOOST_TEST(out2.str() == "45");
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list1.size() == 4);
}
BOOST_AUTO_TEST_CASE(SpliceAfterRange)
{
  FwdList list1{1, 2, 3};
  FwdList list2{4, 5, 6, 7, 8};
  auto begin = ++list2.cbegin();
  auto last = list2.cbegin();
  for (size_t i = 0; i < 4; i++)
  {
    ++last;
  }
  list1.spliceAfter(list1.cbegin(), list2, begin, last);
  std::ostringstream out1;
  printList(out1, list1);
  std::ostringstream out2;
  printList(out2, list2);
  BOOST_TEST(out1.str() == "167823");
  BOOST_TEST(out2.str() == "45");
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list1.size() == 6);
}

BOOST_AUTO_TEST_SUITE_END()

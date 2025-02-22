#include <cstddef>
#include <initializer_list>
#include <sstream>
#include <boost/test/tools/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include "constIterator.hpp"
#include "iterator.hpp"
#include "list.hpp"

using namespace kiselev;
namespace
{
  void createList(List< int >* list, int count)
  {
    for (int i = 0; i < count; ++i)
    {
      list->push_back(i);
    }
  }
  std::ostream& outputList(std::ostream& out, List< int >* list)
  {
    for (ConstIterator< int > it = list->cbegin(); it != list->cend(); ++it)
    {
      out << *it;
    }
    return out;
  }
}
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
  createList(&list, 20);
  ConstIterator< int > begin = list.cbegin();
  Iterator< int > it = list.erase(begin);
  BOOST_CHECK(it == list.begin());
  ConstIterator< int > end = --list.cend();
  it = list.erase(end);
  BOOST_CHECK(it == list.end());
  ConstIterator< int > iter = ++list.cbegin();
  it = list.erase(iter);
  BOOST_CHECK(*it == 3);
  begin = ++list.cbegin();
  end = --list.cend();
  it = list.erase(begin, end);
  BOOST_CHECK(it == --list.end());
}

BOOST_AUTO_TEST_CASE(remove)
{
  List< int > list;
  int i = 0;
  list.push_back(i);
  list.remove(i);
  BOOST_TEST(list.empty());
  createList(&list, 10);
  list.push_back(1);
  list.remove(1);
  BOOST_TEST(list.size() == 9);
}

BOOST_AUTO_TEST_CASE(splice)
{
  List< int > list1;
  createList(&list1, 5);
  List< int > list2;
  createList(&list2, 3);
  ConstIterator< int > it = ++list1.cbegin();
  list1.splice(it, list2);
  std::ostringstream out;
  outputList(out, &list1);
  BOOST_TEST(out.str() == "00121234");
  std::ostringstream out1;
  it = list1.cbegin();
  List< int > list3;
  createList(&list3, 3);
  ConstIterator< int > it2 = --list3.cend();
  list1.splice(it, list3, it2);
  outputList(out1, &list1);
  BOOST_TEST(out1.str() == "200121234");
  List< int > list4;
  createList(&list4, 4);
  it2 = --list4.cend();
  ConstIterator< int > it3 = ++list4.cbegin();
  list1.splice(it, list4, it3, it2);
  std::ostringstream out2;
  outputList(out2, &list1);
  BOOST_TEST(out2.str() == "21200121234");
}

BOOST_AUTO_TEST_CASE(insert_element)
{
  List< int > list;
  list.insert(list.cbegin(), 1);
  BOOST_TEST(list.front() == 1);
  list.insert(list.cbegin(), 3);
  BOOST_TEST(list.front() == 3);
  list.insert(++list.cbegin(), 5);
  BOOST_TEST(*(++list.cbegin()) == 5);
  int i = 7;
  list.insert(list.cbegin(), i);
  BOOST_TEST(list.front() == 7);
}

BOOST_AUTO_TEST_CASE(insert_fill)
{
  List< int > list;
  createList(&list, 5);
  size_t i = 0;
  Iterator< int > res = list.insert(list.cbegin(), i, 3);
  BOOST_TEST((res == list.begin()));
  i = 2;
  res = list.insert(list.cbegin(), i, 7);
  BOOST_TEST(list.front() == 7);
}

BOOST_AUTO_TEST_CASE(insert_range)
{
  List< int > list;
  createList(&list, 5);
  List< int > list2;
  Iterator< int > res = list.insert(list.cbegin(), list2.cbegin(), list2.cend());
  BOOST_TEST((res == list.begin()));
  createList(&list2, 4);
  res = list.insert(list.cbegin(), ++list2.cbegin(), list2.cend());
  BOOST_TEST((res == list.begin()));
}

BOOST_AUTO_TEST_CASE(insert_initializer)
{
  List< int > list;
  createList(&list, 5);
  std::initializer_list< int > il = { 1, 2, 3 };
  Iterator< int > it = list.insert(list.cbegin(), il.begin(), il.end());
  BOOST_TEST((it == list.begin()));
}

BOOST_AUTO_TEST_CASE(assign_fill)
{
  List< int > list;
  size_t size = 20;
  list.assign(size, 10);
  BOOST_TEST(list.size() == size);
  BOOST_TEST(list.front() == 10);
}

BOOST_AUTO_TEST_CASE(assign_range_initializer)
{
  List< int > list;
  List< int > list2;
  createList(&list2, 5);
  list.assign(list2.begin(), list2.end());
  BOOST_TEST(list.size() == 5);
  std::initializer_list< int > il = { 1, 2, 3 };
  list.assign(il);
  BOOST_TEST(list.size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()

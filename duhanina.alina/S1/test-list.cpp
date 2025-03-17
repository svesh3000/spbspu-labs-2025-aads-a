#include <boost/test/unit_test.hpp>
#include "list.hpp"

using list_t = duhanina::List< int >;

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
  list_t list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(test_constructor_with_parameters)
{
  list_t list1(0, 1);
  BOOST_TEST(list1.empty());
  list_t list(3, 5);
  BOOST_TEST(list.size() == 3);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  list_t list3;
  list_t list1(2, 5);
  list_t list2(list1);
  list_t list4(list3);
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list4.empty());
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  list_t list1(2, 2);
  list_t cop = list1;
  list_t list2(std::move(list1));
  BOOST_TEST(list2 == cop);
}

BOOST_AUTO_TEST_CASE(test_push_front)
{
  list_t list;
  list.push_front(1);
  BOOST_TEST(list.front() == 1);
}

BOOST_AUTO_TEST_CASE(test_push_back)
{
  list_t list;
  list.push_back(1);
  BOOST_TEST(list.back() == 1);
}

BOOST_AUTO_TEST_CASE(test_pop_front)
{
  list_t list(2, 2);
  list.pop_front();
  BOOST_TEST(list.front() == 2);
}

BOOST_AUTO_TEST_CASE(test_pop_back)
{
  list_t list(2, 1);
  list_t list1(1, 5);
  list.pop_back();
  BOOST_TEST(list.back() == 1);
  list1.pop_back();
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(test_clear)
{
  list_t list(2, 9);
  list.clear();
  BOOST_TEST(list.empty());
  list_t list1;
  list1.clear();
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(test_remove)
{
  list_t list(2, 2);
  list.remove(2);
  BOOST_TEST(list.empty());
  list_t list1;
  list.remove(2);
  BOOST_TEST(list1.empty());
}

namespace
{
  bool even(int a)
  {
    return a % 2 == 0;
  }
}

BOOST_AUTO_TEST_CASE(test_remove_if)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.remove_if(even);
  BOOST_TEST(list.size() == 2);
  list_t list1;
  list.remove_if(even);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(test_assign)
{
  list_t list(2, 7);
  list.assign(3, 5);
  BOOST_TEST(list.size() == 3);
  list_t list1;
  list.assign(0, 4);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(test_iterators)
{
  list_t list(3, 1);
  auto it = list.begin();
  BOOST_TEST(*it == 1);
  auto it1 = list.end();
  BOOST_TEST(*it1 == 0);
}

BOOST_AUTO_TEST_CASE(test_swap)
{
  list_t list1(3, 1);
  list_t list2(2, 4);
  list1.swap(list2);
  BOOST_TEST(list1.size() == 2);
  BOOST_TEST(list2.size() == 3);
}

BOOST_AUTO_TEST_CASE(test_splice)
{
  list_t list1(3, 3);
  list_t list2(3, 4);
  auto pos = list1.begin();
  ++pos;
  list1.splice(pos, list2);
  BOOST_TEST(list1.size() == 6);
  list_t list3(5, 5);
  list_t cop = list3;
  list_t list4;
  list3.splice(list3.begin(), list4);
  BOOST_TEST(list3 == cop);

  list_t list5(2, 2);
  list_t list6(4, 4);
  auto pos1 = list5.begin();
  ++pos1;
  auto it = list6.begin();
  list5.splice(pos1, list6, ++it);
  BOOST_TEST(list5.size() == 3);
  list_t list7(3, 3);
  list_t cop1 = list7;
  list_t list8(1, 1);
  list7.splice(list7.begin(), list8, list8.end());
  BOOST_TEST(list7 == cop1);

  list_t list9(6, 6);
  list_t list10(7, 7);
  auto pos2 = ++list1.begin();
  auto first = list1.begin();
  auto last = ++list1.begin();
  list9.splice(pos2, list10, first, ++last);
  BOOST_TEST(list9.size() == 8);
  list_t list11(3, 3);
  list_t cop2 = list11;
  list_t list12(1, 1);
  list11.splice(list11.begin(), list12, list12.begin(), list12.begin());
  BOOST_TEST(list11 == cop2);
  list11.splice(list11.begin(), list12, list12.end(), list12.begin());
  BOOST_TEST(list11 == cop2);
}

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
  const list_t cop{ 5, 5, 5 };
  BOOST_TEST(list == cop);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  list_t list3;
  list_t list1(2, 5);
  const list_t cop{ 5, 5 };
  list_t list2(list1);
  list_t list4(list3);
  BOOST_TEST(list2 == cop);
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
  list_t list(3, 3);
  list.push_front(1);
  BOOST_TEST(list.front() == 1);
}

BOOST_AUTO_TEST_CASE(test_push_back)
{
  list_t list(4, 4);
  list.push_back(1);
  BOOST_TEST(list.back() == 1);
}

BOOST_AUTO_TEST_CASE(test_pop_front)
{
  list_t list{ 1, 2, 3 };
  list.pop_front();
  BOOST_TEST(list.front() == 2);
}

BOOST_AUTO_TEST_CASE(test_pop_back)
{
  list_t list{ 2, 1, 4 };
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
  list_t list{ 1, 2, 3, 2 };
  const list_t cop{ 1, 3 };
  list.remove(2);
  BOOST_TEST(list == cop);
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
  list_t list{ 1, 2, 3, 4 };
  const list_t cop{ 1, 3 };
  list.remove_if(even);
  BOOST_TEST(list == cop);
  list_t list1;
  list.remove_if(even);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(test_assign)
{
  list_t list(2, 7);
  list.assign(3, 5);
  const list_t cop{ 5, 5, 5 };
  BOOST_TEST(list == cop);
  list_t list1;
  list.assign(0, 4);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(test_iterators)
{
  list_t list{ 1, 2, 3 };
  auto it = list.begin();
  BOOST_TEST(*it == 1);
  auto it1 = list.end();
  BOOST_TEST(*it1 == 0);
}

BOOST_AUTO_TEST_CASE(test_swap)
{
  list_t list1{ 1, 2, 3 };
  list_t list2{ 4, 5 };
  const list_t cop1 = list1;
  const list_t cop2 = list2;
  list1.swap(list2);
  BOOST_TEST(list1 == cop2);
  BOOST_TEST(list2 == cop1);
}

BOOST_AUTO_TEST_CASE(test_initializer_list)
{
  list_t list1{ 1, 2, 3 };
  list_t list2{};
  BOOST_TEST(list1.size() == 3);
  BOOST_TEST(list2.empty());
}


BOOST_AUTO_TEST_CASE(test_splice)
{
  list_t list1{ 1, 2, 3 };
  list_t list2{ 4, 5 };
  auto pos = list1.begin();
  ++pos;
  const list_t cop1{ 1, 4, 5, 2, 3 };
  list1.splice(pos, list2);
  BOOST_TEST(list1 == cop1);
  list_t list3{ 1, 1 };
  list_t cop2 = list3;
  list_t list4;
  list3.splice(list3.begin(), list4);
  BOOST_TEST(list3 == cop2);

  list_t list5{ 1, 2 };
  list_t list6{ 3, 4 };
  auto pos1 = list5.begin();
  ++pos1;
  auto it = list6.begin();
  const list_t cop3{ 1, 3, 2 };
  list5.splice(pos1, list6, ++it);
  BOOST_TEST(list5 == cop3);
  list_t list7{ 1, 2, 3 };
  list_t cop4 = list7;
  list_t list8(1, 1);
  list7.splice(list7.begin(), list8, list8.end());
  BOOST_TEST(list7 == cop4);

  list_t list9{ 7, 6, 5, 4 };
  list_t list10{ 1, 2, 3, 4 };
  auto pos2 = ++list1.begin();
  auto first = list1.begin();
  auto last = ++list1.begin();
  const list_t cop5{ 7, 1, 2, 6, 5, 4 };
  list9.splice(pos2, list10, first, ++last);
  BOOST_TEST(list9 == cop5);
  list_t list11{ 1, 2, 3 };
  list_t cop6 = list11;
  list_t list12(1, 1);
  list11.splice(list11.begin(), list12, list12.begin(), list12.begin());
  BOOST_TEST(list11 == cop6);
  list11.splice(list11.begin(), list12, list12.end(), list12.begin());
  BOOST_TEST(list11 == cop6);
}

#include <boost/test/unit_test.hpp>
#include "list.hpp"
#include "iterators.hpp"
#include "listNode.hpp"

using list_t = alymova::List< int >;
using iter_t = alymova::Iterator< int >;
using citer_t = alymova::ConstIterator< int >;
using list_pair_t = alymova::List< std::pair< std::string, int > >;
/*BOOST_AUTO_TEST_CASE(test_constructors_operators)
{
  list_pair_t list;
  BOOST_TEST(list.size() == 0);
}*/
BOOST_AUTO_TEST_CASE(test_constructors_operators)
{
  list_t list1 = {3, 1};
  list_t list2(list1);
  BOOST_TEST(list1 == list2);

  list_t list3(std::move(list_t{3, 1}));
  BOOST_TEST(list1 == list3);

  list_t list4 = {5, 2};
  list3 = list4;
  BOOST_TEST(list3 == list4);

  list4 = list_t{3, 1};
  BOOST_TEST(list4 == list1);
}
BOOST_AUTO_TEST_CASE(test_list_iterators)
{
  list_t list = {3, 1};
  iter_t iter_b = list.begin();
  iter_t iter_e = list.end();
  BOOST_TEST(*iter_b == 1);
  BOOST_TEST(*iter_e == 0);

  const list_t list1 = {2, 3};
  citer_t citer_b = list1.cbegin();
  citer_t citer_e = list1.cend();
  BOOST_TEST(*citer_b == 3);
  BOOST_TEST(*citer_e == 0);
}
BOOST_AUTO_TEST_CASE(test_size)
{
  list_t list;
  BOOST_TEST(list.size() == 0);

  int x = 1;
  list.push_back(x);
  BOOST_TEST(list.size() == 1);

  list.pop_back();
  BOOST_TEST(list.empty());
}
BOOST_AUTO_TEST_CASE(test_front)
{
  list_t list;
  int x = 1;
  list.push_front(x);
  BOOST_TEST(list.front() == 1);

  x = 2;
  list.push_front(x);
  BOOST_TEST(list.back() == 2);
}
BOOST_AUTO_TEST_CASE(test_base_interface)
{
  list_t list;
  BOOST_TEST(list.size() == 0);
  BOOST_TEST(list.empty());

  int x = 1;
  list.push_front(x);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.size() == 1);

  x = 2;
  list.push_front(x);
  BOOST_TEST(list.back() == 2);

  list.pop_front();
  BOOST_TEST(list.front() == 2);
  list.pop_back();
  BOOST_TEST(list.empty());

  int x1 = 10, x2 = 20, x3 = 30;
  list.push_back(x1);
  list.push_back(x2);
  list.push_back(x3);
  BOOST_TEST(list.front() == 10);
  BOOST_TEST(list.back() == 20);
  BOOST_TEST(*(++list.begin()) == 30);
  BOOST_TEST(list.size() == 3);

  list.pop_back();
  BOOST_TEST(list.back() == 20);
}

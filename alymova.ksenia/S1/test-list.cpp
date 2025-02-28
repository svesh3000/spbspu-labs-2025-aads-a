#include <boost/test/unit_test.hpp>
#include "list.hpp"
#include "iterators.hpp"
#include "listNode.hpp"

using list_t = alymova::List< int >;
using iter_t = alymova::Iterator< int >;
using citer_t = alymova::ConstIterator< int >;
using list_str_t = alymova::List< std::string >;
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
  BOOST_TEST(list4 != list3);
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

  citer_b = list1.begin();
  citer_e = list1.end();
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
BOOST_AUTO_TEST_CASE(test_base_interface)
{
  list_t list;
  BOOST_TEST(list.size() == 0);
  BOOST_TEST(list.empty());

  list.push_front(1);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.size() == 1);

  list.push_front(2);
  BOOST_TEST(list.back() == 1);

  list.pop_front();
  BOOST_TEST(list.front() == 1);

  list.pop_back();
  BOOST_TEST(list.empty());

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  BOOST_TEST(list.front() == 10);
  BOOST_TEST(list.back() == 30);
  BOOST_TEST(*(++list.begin()) == 20);
  BOOST_TEST(list.size() == 3);

  list.pop_back();
  BOOST_TEST(list.back() == 20);

  const list_t list1 = {3, 1};
  BOOST_TEST(list1.front() == 1);
  BOOST_TEST(list1.back() == 1);
}
BOOST_AUTO_TEST_CASE(test_swap)
{
  list_t list1 = {2, 5};
  list_t list2 = {5, 2};
  list_t list3 = list2;
  list1.swap(list2);
  BOOST_TEST(list1 == list3);
}
BOOST_AUTO_TEST_CASE(test_remove)
{
  list_str_t list = {1, "cat"};
  list.remove("cat");
  BOOST_TEST(list.size() == 0);

  list.push_back("dog");
  list.push_back("student");
  list.remove("student");
  BOOST_TEST(list.back() == "dog");

  list_str_t list1 = {10, "cat"};
  list1.push_back("fox");
  list1.push_front("dolphin");
  list1.remove("cat");
  BOOST_TEST(list1.size() == 2);
}

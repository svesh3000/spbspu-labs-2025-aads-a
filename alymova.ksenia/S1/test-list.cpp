#include <boost/test/unit_test.hpp>
#include "list.hpp"
#include "iterators.hpp"
#include "listNode.hpp"

BOOST_AUTO_TEST_CASE(test_constructors_operators)
{
  using list_t = alymova::List< int >;

  list_t list1;
  BOOST_TEST(list1.empty());
  list_t list2(list1);
  BOOST_TEST(list1 == list2);

  list_t list3(std::move(list_t(static_cast< size_t >(3), 1)));
  BOOST_TEST(list3.size() == 3);
  BOOST_TEST(list3.front() == 1);

  list_t list4(list3.begin(), list3.end());
  BOOST_TEST(list4 == list3);

  list_t list5({1, 1, 1});
  BOOST_TEST(list5 == list3);

  list3 = list4;
  BOOST_TEST(list3 == list4);

  list4 = list_t(static_cast< size_t >(3), 1);
  BOOST_TEST(list4 == list5);

  list4 = {2, 2, 2};
  list_t list6{2, 2, 2};
  BOOST_TEST(list4 == list6);
}
BOOST_AUTO_TEST_CASE(test_list_iterators)
{
  using list_t = alymova::List< int >;

  list_t list(static_cast< size_t >(3), 1);
  auto iter_b = list.begin();
  auto iter_e = list.end();
  BOOST_TEST(*iter_b == 1);
  BOOST_TEST(*iter_e == 0);

  const list_t list1(static_cast< size_t >(2), 3);
  auto citer_b = list1.cbegin();
  auto citer_e = list1.cend();
  BOOST_TEST(*citer_b == 3);
  BOOST_TEST(*citer_e == 0);

  citer_b = list1.begin();
  citer_e = list1.end();
  BOOST_TEST(*citer_b == 3);
  BOOST_TEST(*citer_e == 0);
}
BOOST_AUTO_TEST_CASE(test_size)
{
  using list_t = alymova::List< int >;

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
  using list_t = alymova::List< int >;

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

  const list_t list1((size_t)3, 1);
  BOOST_TEST(list1.front() == 1);
  BOOST_TEST(list1.back() == 1);
}
BOOST_AUTO_TEST_CASE(test_swap)
{
  using list_t = alymova::List< int >;

  list_t list1 = {2, 5};
  list_t list2 = {5, 2};
  list_t list3 = list2;
  list1.swap(list2);
  BOOST_TEST(list1 == list3);
}

bool is_divided_10(const int& value)
{
  return value % 10 == 0;
}
struct SingleDigit
{
  bool operator()(const int& value)
  {
    return (value < 10 && value > -10);
  }
};
BOOST_AUTO_TEST_CASE(test_remove)
{
  using list_t = alymova::List< int >;
  using list_str_t = alymova::List< std::string >;

  list_str_t list1(1, "cat");
  list1.remove("cat");
  BOOST_TEST(list1.size() == 0);

  list1.push_back("dog");
  list1.push_back("student");
  list1.remove("student");
  BOOST_TEST(list1.back() == "dog");

  list_str_t list2(10, "cat");
  list2.push_back("fox");
  list2.push_front("dolphin");
  list2.remove("cat");
  BOOST_TEST(list2.size() == 2);

  list_t list3((size_t)5, 10);
  list3.push_back(1);

  list3.remove_if(SingleDigit());
  BOOST_TEST(list3.size() == 5);
  BOOST_TEST(list3.back() == 10);

  list3.push_back(11);
  list3.remove_if(is_divided_10);
  BOOST_TEST(list3.size() == 1);
  BOOST_TEST(list3.front() == 11);
}
BOOST_AUTO_TEST_CASE(test_assign)
{
  using list_t = alymova::List< int >;
  list_t list1;
  list1.assign(5, 1);
  list_t list2(static_cast< size_t >(5), 1);
  BOOST_TEST(list1 == list2);
}
BOOST_AUTO_TEST_CASE(test_splice)
{
  using list_t = alymova::List< int >;
  list_t list1, list2;
  for (size_t i = 1; i <= 4; i++)
  {
    list1.push_back(i);
  }
  for (size_t i = 1; i <= 3; i++)
  {
    list2.push_back(i * 10);
  }
  auto iter1 = list2.begin();
  list1.splice(list1.begin(), list2, iter1); //10 1 2 3 4; 20 30
  BOOST_TEST(list1.front() == 10);
  BOOST_TEST(list2.front() == 20);
  BOOST_TEST(*iter1 == 10);
  BOOST_TEST(list1.size() == 5);
  BOOST_TEST(list2.size() == 2);

  auto iter2 = --list2.end();
  list1.splice(list1.begin(), list2, iter2); //30 10 1 2 3 4; 20
  BOOST_TEST(list1.front() == 30);
  BOOST_TEST(list2.front() == 20);
  BOOST_TEST(*iter2 == 30);
  BOOST_TEST(list1.size() == 6);
  BOOST_TEST(list2.size() == 1);

  auto iter3 = list2.begin();
  list1.splice(--list1.end(), list2, iter3); //30 10 1 2 3 20 4;
  BOOST_TEST(*iter3 == 20);
  BOOST_TEST(*(++iter3) == 4);
  BOOST_TEST(list1.size() == 7);
  BOOST_TEST(list2.empty());

  for (size_t i = 1; i <= 3; i++)
  {
    list2.push_back(i * 100);
  }
  list2.splice(--list2.end(), list1, iter3); // 30 10 1 2 3 4; 100 200 4 300
  BOOST_TEST(list1.back() == 20);
  BOOST_TEST(*(++iter3) == 300);
  BOOST_TEST(list1.size() == 6);
  BOOST_TEST(list2.size() == 4);

  list_t list3;
  list_t list2_copy = list2;
  list2.splice(list2.begin(), list3);
  BOOST_TEST(list2 == list2_copy);

  list2.splice(list2.begin(), list3, list3.begin(), list3.end());
  BOOST_TEST(list2 == list2_copy);
}
BOOST_AUTO_TEST_CASE(test_insert)
{
  using list_t = alymova::List< int >;
  list_t list1{1, 2, 3};
  alymova::Iterator< int > it_res = list1.insert(list1.begin(), 10);
  list_t list_comp{10, 1, 2, 3};
  BOOST_TEST(*it_res = 10);
  BOOST_TEST(list1 == list_comp);

  it_res = list1.insert(list1.end(), 20);
  list_comp.push_back(20);
  BOOST_TEST(list1 == list_comp);
  BOOST_TEST(*it_res = 20);

  it_res = list1.insert(++(list1.begin()), 30);
  list_comp = {10, 30, 1, 2, 3, 20};
  BOOST_TEST(list1 == list_comp);
  BOOST_TEST(*it_res == 30);

  list1 = {1, 2, 3};
  list_comp = {4, 4, 4, 1, 2, 3};
  it_res = list1.insert(list1.begin(), (size_t)3, 4);
  BOOST_TEST(list1 == list_comp);
  BOOST_TEST(*it_res == 4);

  list_t list2;
  it_res = list2.insert(list2.begin(), list1.begin(), list1.end());
  BOOST_TEST(list2 == list_comp);
  BOOST_TEST(*it_res == 4);

  list2.clear();
  it_res = list2.insert(list2.begin(), {4, 4, 4, 1, 2, 3});
  BOOST_TEST(list2 == list_comp);
  BOOST_TEST(*it_res == 4);
}

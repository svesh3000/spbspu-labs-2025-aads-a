#include <boost/test/unit_test.hpp>
#include <string>
#include "list.hpp"
#include "test-common.hpp"

template< typename T >
using lt = savintsev::List< T >;

//default

BOOST_AUTO_TEST_CASE(test_fill_constructor)
{
  lt< int > list1(8, 0);
  auto it = list1.cbegin();
  for (size_t i = 0; i < 8; ++i)
  {
    BOOST_TEST(*it == 0);
  }
  BOOST_TEST(list1.size() == 8);
}

//range

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  lt< std::string > list1;
  list1.push_back("banana");
  list1.push_back("orange");
  list1.push_front("apple");
  lt< std::string > list2(list1);
  auto it = list2.begin();
  BOOST_TEST(*it == "apple");
  ++it;
  BOOST_TEST(*it == "banana");
  ++it;
  BOOST_TEST(*it == "orange");
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  lt< std::string > list1;
  list1.push_back("banana");
  list1.push_back("orange");
  list1.push_front("apple");
  lt< std::string > list2(std::move(list1));
  auto it = list2.begin();
  BOOST_TEST(*it == "apple");
  ++it;
  BOOST_TEST(*it == "banana");
  ++it;
  BOOST_TEST(*it == "orange");
}

//initial list

BOOST_AUTO_TEST_CASE(test_assign)
{
  savintsev::List< int > list1;
  savintsev::List< int > list2;
  list1.assign(7, 100);
  auto it = list1.begin();
  for (size_t i = 0; i < 7; ++i)
  {
    BOOST_TEST(*it++ == 100);
  }
  list2.assign(list1.begin(), list1.end());
  auto jt = list2.begin();
  for (size_t i = 0; i < 7; ++i)
  {
    BOOST_TEST(*jt++ == 100);
  }
}

BOOST_AUTO_TEST_CASE(test_begin_and_end)
{
  int myints[] = {75,23,65,42,13};
  lt< int > mylist(myints, myints + 5);

  for (lt< int >::iterator it = mylist.begin(); it != mylist.end(); ++it)
  {
    *it = 18;
  }

  lt< int > eighteens(5, 18); 
  BOOST_CHECK_EQUAL_COLLECTIONS(mylist.begin(), mylist.end(), eighteens.begin(), eighteens.end());
}

BOOST_AUTO_TEST_CASE(test_cbegin_and_cend)
{
  
}

BOOST_AUTO_TEST_CASE(test_clear)
{
  lt< int > mylist;
  mylist.push_back (100);
  mylist.push_back (200);
  mylist.push_back (300);
  mylist.clear();
  mylist.push_back (1101);
  mylist.push_back (2202);
  int test[] = {1101, 2202};
  BOOST_CHECK_EQUAL_COLLECTIONS(mylist.begin(), mylist.end(), test, test + 2);
}

//emplace

BOOST_AUTO_TEST_CASE(test_empty)
{
  lt< int > mylist;
  int sum = 0;

  for (int i = 1; i <= 10; ++i)
  {
    mylist.push_back(i);
  }
  while (!mylist.empty())
  {
    sum += mylist.front();
    mylist.pop_front();
  }

  BOOST_TEST(sum == 55);
}

//erase

BOOST_AUTO_TEST_CASE(test_front_and_back)
{
  lt< int > mylist;
  mylist.push_back(77);
  mylist.push_back(22);

  mylist.front() -= mylist.back();

  BOOST_TEST(mylist.front() == 55);
}

//insert

//merge

//operator=

BOOST_AUTO_TEST_CASE(test_push_and_pop)
{
  lt< std::string > list1;
  list1.push_back("1");
  list1.push_back("2");
  list1.push_front("0");
  {
    std::string test[] = {"0", "1", "2"};
    BOOST_CHECK_EQUAL_COLLECTIONS(list1.begin(), list1.end(), test, test + 3);
  }
  list1.pop_front();
  list1.pop_back();
  {
    std::string test[] = {"1"};
    BOOST_CHECK_EQUAL_COLLECTIONS(list1.begin(), list1.end(), test, test + 1);
  }
  BOOST_TEST(list1.size() == 1);
}

BOOST_AUTO_TEST_CASE(test_remove)
{
  savintsev::List< int > list1;
  list1.push_back(0);
  list1.push_back(0);
  list1.push_back(4);
  list1.push_back(0);
  list1.push_back(4);
  list1.remove(4);
  for (auto it = list1.begin(); it != list1.end(); ++it)
  {
    BOOST_TEST(*it == 0);
  }
}

BOOST_AUTO_TEST_CASE(test_remove_if)
{
  savintsev::List< int > list1;
  for (size_t i = 1; i <= 10; ++i)
  {
    list1.push_back(i);
  }
  list1.remove_if(savintsev::divisible_by_five);
  list1.remove_if(savintsev::is_even());
  size_t i = 1;
  for (auto it = list1.begin(); it != list1.end(); ++it)
  {
    BOOST_TEST(*it == i);
    i += (i == 3) ? 4 : 2;
  }
}

//reverse

BOOST_AUTO_TEST_CASE(test_size)
{
  lt< int > myints;
  BOOST_TEST(myints.size() == 0);

  for (int i = 0; i < 10; i++)
  {
    myints.push_back(i);
  }
  BOOST_TEST(myints.size() == 10);
  myints.insert(myints.begin(), 10, 100);
  BOOST_TEST(myints.size() == 20);
  myints.pop_back();
  BOOST_TEST(myints.size() == 19);
}

//sort

BOOST_AUTO_TEST_CASE(test_splice)
{
  lt< int > mylist1, mylist2;
  lt< int >::iterator it;

  for (int i = 1; i <= 4; ++i)
  {
    mylist1.push_back(i);
  }
  for (int i = 1; i <= 3; ++i)
  {
    mylist2.push_back(i * 10);
  }
  it = mylist1.begin();
  ++it;
  mylist1.splice (it, mylist2);
  {
    lt< int > test1 = {1, 10, 20, 30, 2, 3, 4};
    BOOST_TEST(mylist1 == test1);
    BOOST_TEST(mylist2.empty());
    BOOST_TEST(*it == 2);
  }
  mylist2.splice(mylist2.begin(), mylist1, it);
  {
    lt< int > test1 = {1, 10, 20, 30, 3, 4};
    lt< int > test2 = {2};
    BOOST_TEST(mylist2 == test2);
    BOOST_TEST(*it == 2);
  }
  it = mylist1.begin();
  std::advance(it, 3);
  BOOST_TEST(*it == 30);
  mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
  {
    lt< int > test1 = {30, 3, 4, 1, 10, 20};
    BOOST_TEST(mylist1 == test1);
  }
}

BOOST_AUTO_TEST_CASE(test_swap)
{
  lt< int > first(3, 100);
  lt< int > second(5, 200);

  first.swap(second);

  int first_test[] = {200, 200, 200, 200, 200};
  int second_test[] = {100, 100, 100};

  BOOST_CHECK_EQUAL_COLLECTIONS(first.begin(), first.end(), first_test, first_test + 5);
  BOOST_CHECK_EQUAL_COLLECTIONS(second.begin(), second.end(), second_test, second_test + 3);

  BOOST_TEST(first.size() == 5);
  BOOST_TEST(second.size() == 3);
}

//unique

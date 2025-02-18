#include <boost/test/unit_test.hpp>
#include <string>
#include "list.hpp"
#include "list-algorithms.hpp"

BOOST_AUTO_TEST_CASE(list_test)
{
  std::string out;
  savintsev::List<std::string> list;
  list.push_back("test1234");
  BOOST_TEST(!list.empty());
  BOOST_TEST(list.size() == 1);
  list.pop_front();
  BOOST_TEST(list.size() == 0);
  list.push_back("test1234");
  list.push_front("test8765");
  list.clear();
  BOOST_TEST(list.empty());
  list.push_front("test");
  BOOST_TEST(list.front() == "test");
  list.push_back("hello");
  BOOST_TEST(list.back() == "hello");
  savintsev::List<std::string> list1;
  list1.push_back("hotdog");
  list.swap(list1);
  BOOST_TEST(list.back() == "hotdog");
  BOOST_TEST(list1.back() == "hello");
  list1.push_back("lemonade");
}

BOOST_AUTO_TEST_CASE(test_begin_and_end)
{
  savintsev::List<std::string> list1;
  list1.push_back("front");
  list1.push_back("back");
  auto it = list1.begin();
  BOOST_TEST(*it == "front");
  auto jt = list1.end();
  --jt;
  BOOST_TEST(*jt == "back");
}

BOOST_AUTO_TEST_CASE(test_front_and_back)
{
  savintsev::List<std::string> list1;
  list1.push_back("front");
  list1.push_back("back");
  BOOST_TEST(list1.front() == "front");
  BOOST_TEST(list1.back() == "back");
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  savintsev::List<std::string> list1;
  list1.push_back("banana");
  list1.push_back("orange");
  list1.push_front("apple");
  savintsev::List<std::string> list2(list1);
  auto it = list2.begin();
  BOOST_TEST(*it == "apple");
  ++it;
  BOOST_TEST(*it == "banana");
  ++it;
  BOOST_TEST(*it == "orange");
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  savintsev::List<std::string> list1;
  list1.push_back("banana");
  list1.push_back("orange");
  list1.push_front("apple");
  savintsev::List<std::string> list2(std::move(list1));
  auto it = list2.begin();
  BOOST_TEST(*it == "apple");
  ++it;
  BOOST_TEST(*it == "banana");
  ++it;
  BOOST_TEST(*it == "orange");
}

BOOST_AUTO_TEST_CASE(test_fill)
{
  savintsev::List<int> list1;
  for (size_t i = 0; i < 8; ++i)
  {
    list1.push_back(0);
  }
  savintsev::fill(list1.begin(), --list1.end(), 5);
  auto it = list1.begin();
  for (size_t i = 0; i < 7; ++i)
  {
    BOOST_TEST(*it == 5);
  }
  BOOST_TEST(list1.back() == 0);
}

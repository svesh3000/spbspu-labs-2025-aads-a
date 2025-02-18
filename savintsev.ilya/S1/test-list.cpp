#include <boost/test/unit_test.hpp>
#include <string>
#include "list.hpp"
#include "list-algorithms.hpp"

BOOST_AUTO_TEST_CASE(test_swap)
{
  std::string out;
  savintsev::List<std::string> meats;
  meats.push_back("hotdog");
  meats.push_back("pierogi");
  meats.push_back("beef");
  savintsev::List<std::string> vegetables;
  vegetables.push_back("latuce");
  vegetables.push_back("tomato");
  meats.swap(vegetables);
  BOOST_TEST(meats.front() == "latuce");
  BOOST_TEST(vegetables.front() == "hotdog");
  BOOST_TEST(meats.back() == "tomato");
  BOOST_TEST(vegetables.back() == "beef");
}

BOOST_AUTO_TEST_CASE(test_std_interface)
{
  savintsev::List<std::string> list1;
  BOOST_TEST(list1.empty());
  BOOST_TEST(list1.size() == 0);
  list1.push_back("test");
  BOOST_TEST(!list1.empty());
  list1.push_front("another_test");
  BOOST_TEST(list1.size() == 2);
  list1.pop_front();
  BOOST_TEST(list1.size() == 1);
  BOOST_TEST(list1.front() == "test");
  list1.push_back("onemore_test");
  list1.pop_back();
  BOOST_TEST(list1.back() == "test");
  list1.clear();
  BOOST_TEST(list1.empty());
  BOOST_TEST(list1.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_push_and_pop)
{
  savintsev::List<std::string> list1;
  list1.push_back("1");
  list1.push_back("2");
  list1.push_front("0");
  auto it = list1.begin();
  BOOST_TEST(*it == "0");
  ++it;
  BOOST_TEST(*it == "1");
  ++it;
  BOOST_TEST(*it == "2");
  list1.pop_front();
  auto jt = list1.begin();
  BOOST_TEST(*jt++ == "1");
  BOOST_TEST(*jt == "2");
}

BOOST_AUTO_TEST_CASE(test_begin_and_end)
{
  savintsev::List<std::string> list1;
  list1.push_back("front");
  list1.push_back("back");
  auto it = list1.begin();
  BOOST_TEST(*it == "front");
  auto jt = list1.end();
  BOOST_TEST(*--jt == "back");
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

BOOST_AUTO_TEST_CASE(test_remove)
{
  savintsev::List<int> list1;
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

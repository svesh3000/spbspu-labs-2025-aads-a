#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(iterators_tests)

BOOST_AUTO_TEST_CASE(begin_end_test)
{
  shramko::FwdList< int > list;
  list.push_front(1);
  list.push_front(2);
  
  auto it = list.begin();
  BOOST_TEST(*it == 2);
  
  ++it;
  BOOST_TEST(*it == 1);
  
  ++it;
  BOOST_TEST(it == list.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(element_access_tests)

BOOST_AUTO_TEST_CASE(front_empty_list)
{
  shramko::FwdList< int > list;
  BOOST_CHECK_THROW(list.front(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(front_modification)
{
  shramko::FwdList< int > list;
  list.push_front(1);
  list.front() = 42;
  BOOST_TEST(list.front() == 42);
}

BOOST_AUTO_TEST_CASE(back_empty_list)
{
  shramko::FwdList< int > list;
  BOOST_CHECK_THROW(list.back(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(back_modification)
{
  shramko::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  list.back() = 99;
  BOOST_TEST(list.back() == 99);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(capacity_tests)

BOOST_AUTO_TEST_CASE(size_after_operations)
{
  shramko::FwdList< int > list;
  BOOST_TEST(list.size() == 0);
  
  list.push_front(1);
  list.push_back(2);
  BOOST_TEST(list.size() == 2);
  
  list.pop_front();
  BOOST_TEST(list.size() == 1);
  
  list.clear();
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(empty_after_clear)
{
  shramko::FwdList< int > list;
  list.push_back(1);
  BOOST_TEST(!list.empty());
  
  list.clear();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(modifiers_tests)

BOOST_AUTO_TEST_CASE(push_pop_front)
{
  shramko::FwdList< int > list;
  list.push_front(3);
  list.push_front(2);
  list.push_front(1);
  
  BOOST_TEST(list.front() == 1);
  list.pop_front();
  BOOST_TEST(list.front() == 2);
  list.pop_front();
  BOOST_TEST(list.front() == 3);
}

BOOST_AUTO_TEST_CASE(push_back_sequence)
{
  shramko::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  
  auto it = list.begin();
  BOOST_TEST(*it == 1);
  ++it;
  BOOST_TEST(*it == 2);
  ++it;
  BOOST_TEST(*it == 3);
}

BOOST_AUTO_TEST_CASE(swap_lists)
{
  shramko::FwdList< int > list1;
  list1.push_back(1);
  list1.push_back(2);
  
  shramko::FwdList< int > list2;
  list2.push_back(3);
  
  list1.swap(list2);
  
  BOOST_TEST(list1.front() == 3);
  BOOST_TEST(list2.front() == 1);
  BOOST_TEST(list1.size() == 1);
  BOOST_TEST(list2.size() == 2);
}

BOOST_AUTO_TEST_CASE(clear_operations)
{
  shramko::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  list.clear();
  
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0);
  BOOST_CHECK_THROW(list.front(), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(edge_cases)

BOOST_AUTO_TEST_CASE(single_element_list)
{
  shramko::FwdList< int > list;
  list.push_front(42);
  
  BOOST_TEST(list.front() == 42);
  BOOST_TEST(list.back() == 42);
  BOOST_TEST(list.size() == 1);
  
  list.pop_front();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(move_semantics)
{
  shramko::FwdList< int > list1;
  list1.push_back(1);
  list1.push_back(2);
  
  shramko::FwdList< int > list2(std::move(list1));
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_SUITE_END()
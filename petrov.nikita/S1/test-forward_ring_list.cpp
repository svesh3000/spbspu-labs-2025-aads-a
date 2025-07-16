#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include <sstream>
#include "forward_ring_list.hpp"

BOOST_AUTO_TEST_SUITE(forward_ring_list_iterator)


BOOST_AUTO_TEST_SUITE(comparison_operators)

BOOST_AUTO_TEST_CASE(not_equal)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  fwd_list.push_front(3);
  auto it_begin = fwd_list.begin();
  auto it_end = fwd_list.end();
  out << std::boolalpha << (it_begin != it_end);
  BOOST_TEST(out.str() == "true");
}

BOOST_AUTO_TEST_CASE(equal)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  fwd_list.push_front(3);
  auto it_begin = fwd_list.begin();
  auto it_end = fwd_list.end();
  out << std::boolalpha << (it_begin == (++it_end));
  BOOST_TEST(out.str() == "true");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(prefix_increment)

BOOST_AUTO_TEST_CASE(prefix_increment_one_element)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  auto it = fwd_list.begin();
  out << *(++it);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(prefix_increment_two_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  auto it = fwd_list.begin();
  out << *(++it);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(ring_test)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  auto it = fwd_list.begin();
  ++it;
  out << *(++it);
  BOOST_TEST(out.str() == "2");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(postfix_increment)

BOOST_AUTO_TEST_CASE(postfix_increment_one_element)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  auto it = fwd_list.begin();
  out << *(it++);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(postfix_increment_two_element)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  auto it = fwd_list.begin();
  out << *(it++);
  BOOST_TEST(out.str() == "2");
}

BOOST_AUTO_TEST_CASE(ring_test)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  auto it = fwd_list.begin();
  it++;
  it++;
  out << *it;
  BOOST_TEST(out.str() == "2");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE(forward_ring_list)


BOOST_AUTO_TEST_SUITE(push_front_method)

BOOST_AUTO_TEST_CASE(push_front_one_element)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  out << *fwd_list.begin();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(push_front_two_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  out << *fwd_list.begin() << " " << *fwd_list.end();
  BOOST_TEST(out.str() == "2 1");
}

BOOST_AUTO_TEST_CASE(push_front_many_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list;
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  for (auto it = fwd_list.begin(); it != fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *fwd_list.end();
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(reverse_method)

BOOST_AUTO_TEST_CASE(reverse_empty_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.reverse();
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(reverse_list_with_one_element)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.reverse();
  out << *fwd_list.begin() << " " << *fwd_list.end();
  BOOST_TEST(out.str() == "1 1");
}

BOOST_AUTO_TEST_CASE(reverse_list_with_two_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  fwd_list.reverse();
  out << *fwd_list.begin() << " " << *fwd_list.end();
  BOOST_TEST(out.str() == "1 2");
}

BOOST_AUTO_TEST_CASE(reverse_list_with_three_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.reverse();
  for (auto it = fwd_list.begin(); it != fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *fwd_list.end();
  BOOST_TEST(out.str() == "1 2 3");
}

BOOST_AUTO_TEST_CASE(reverse_list_with_many_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.reverse();
  for (auto it = fwd_list.begin(); it != fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *fwd_list.end();
  BOOST_TEST(out.str() == "1 2 3 4 5 6 7 8 9 10");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(copy_constuctor)

BOOST_AUTO_TEST_CASE(make_list_from_other_which_is_empty)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list;
  petrov::ForwardRingList< int > second_fwd_list(first_fwd_list);
  out << second_fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(make_list_from_other_with_one_element)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list;
  first_fwd_list.push_front(1);
  petrov::ForwardRingList< int > second_fwd_list(first_fwd_list);
  out << *second_fwd_list.begin();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(make_list_from_other_with_two_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list;
  first_fwd_list.push_front(1);
  first_fwd_list.push_front(2);
  petrov::ForwardRingList< int > second_fwd_list(first_fwd_list);
  out << *second_fwd_list.begin() << " " << *second_fwd_list.end();
  BOOST_TEST(out.str() == "2 1");
}

BOOST_AUTO_TEST_CASE(make_list_from_other_with_many_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    first_fwd_list.push_front(i);
  }
  petrov::ForwardRingList< int > second_fwd_list(first_fwd_list);
  for (auto it = second_fwd_list.begin(); it != second_fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *second_fwd_list.end();
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(clear_method)

BOOST_AUTO_TEST_CASE(clear_empty_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  first_fwd_list.clear();
  out << first_fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(clear_list_with_one_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  first_fwd_list.push_front(1);
  first_fwd_list.clear();
  out << first_fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(clear_list_with_many_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    first_fwd_list.push_front(i);
  }
  first_fwd_list.clear();
  out << first_fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(assign)

BOOST_AUTO_TEST_CASE(assign_empty_list_from_other)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    first_fwd_list.push_front(i);
  }
  second_fwd_list = first_fwd_list;
  for (auto it = second_fwd_list.begin(); it != second_fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *second_fwd_list.end();
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 1");
}

BOOST_AUTO_TEST_CASE(assign_one_element_list_from_other)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    first_fwd_list.push_front(i);
  }
  second_fwd_list.push_front(1);
  second_fwd_list = first_fwd_list;
  for (auto it = second_fwd_list.begin(); it != second_fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *second_fwd_list.end();
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 1");
}

BOOST_AUTO_TEST_CASE(assign_two_element_list_from_other)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    first_fwd_list.push_front(i);
  }
  second_fwd_list.push_front(1);
  second_fwd_list.push_front(2);
  second_fwd_list = first_fwd_list;
  for (auto it = second_fwd_list.begin(); it != second_fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *second_fwd_list.end();
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 1");
}

BOOST_AUTO_TEST_CASE(assign_many_element_list_from_other)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    first_fwd_list.push_front(i);
  }
  for (int i = 10; i >= 1; i--)
  {
    second_fwd_list.push_front(i);
  }
  second_fwd_list = first_fwd_list;
  for (auto it = second_fwd_list.begin(); it != second_fwd_list.end(); ++it)
  {
    out << *it << " ";
  }
  out << *second_fwd_list.end();
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 1");
}

BOOST_AUTO_TEST_CASE(assign_many_element_list_from_empty_other)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 10; i >= 1; i--)
  {
    second_fwd_list.push_front(i);
  }
  second_fwd_list = first_fwd_list;
  out << second_fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(pop_front_method)

BOOST_AUTO_TEST_CASE(pop_front_empty_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.pop_front();
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(pop_front_one_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.pop_front();
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(pop_front_two_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  fwd_list.pop_front();
  auto it = fwd_list.cbegin();
  out << *it << " " << *(++it);
  BOOST_TEST(out.str() == "1 1");
}

BOOST_AUTO_TEST_CASE(pop_front_three_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.push_front(2);
  fwd_list.push_front(3);
  fwd_list.pop_front();
  auto it = fwd_list.cbegin();
  out << *it << " " << *(++it) << " " <<  *(++it);
  BOOST_TEST(out.str() == "2 1 2");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(remove_method)

BOOST_AUTO_TEST_CASE(remove_element_from_empty_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.remove(1);
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(remove_element_from_one_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.remove(1);
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(remove_element_from_list_filled_with_it)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 0; i < 10; i++)
  {
    fwd_list.push_front(1);
  }
  fwd_list.remove(1);
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(remove_element_from_list_which_are_not_there)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.remove(11);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 1");
}

BOOST_AUTO_TEST_CASE(remove_element_from_start_of_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.remove(10);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  out << " " << *it;
  BOOST_TEST(out.str() == "9 8 7 6 5 4 3 2 1 9");
}

BOOST_AUTO_TEST_CASE(remove_element_from_end_of_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.remove(1);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  out << " " << *it;
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2 10");
}

BOOST_AUTO_TEST_CASE(remove_elements_from_list_which_are_there)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.remove(1);
  fwd_list.remove(10);
  fwd_list.remove(7);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "9 8 6 5 4 3 2");
}

BOOST_AUTO_TEST_CASE(remove_elements_from_list_to_make_it_empty)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    fwd_list.push_front(i);
  }
  for (int i = 1; i <= 3; i++)
  {
    fwd_list.remove(i);
  }
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(are_equal_comparasion_operator)

BOOST_AUTO_TEST_CASE(compare_empty_lists)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  out << (first_fwd_list == second_fwd_list);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(compare_empty_list_with_not_empty)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  second_fwd_list.push_front(1);
  out << (first_fwd_list == second_fwd_list);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(compare_two_equal_not_empty_lists)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    first_fwd_list.push_front(i);
    second_fwd_list.push_front(i);
  }
  out << (first_fwd_list == second_fwd_list);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(compare_two_not_equal_not_empty_lists_different_size)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    first_fwd_list.push_front(i);
    second_fwd_list.push_front(4 - i);
  }
  second_fwd_list.pop_front();
  out << (first_fwd_list == second_fwd_list);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(compare_two_not_equal_not_empty_lists_one_size)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    first_fwd_list.push_front(i);
    second_fwd_list.push_front(4 - i);
  }
  out << (first_fwd_list == second_fwd_list);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(are_not_equal_comparasion_operator)

BOOST_AUTO_TEST_CASE(compare_empty_lists)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  out << (first_fwd_list != second_fwd_list);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(compare_empty_list_with_not_empty)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  second_fwd_list.push_front(1);
  out << (first_fwd_list != second_fwd_list);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(compare_two_equal_not_empty_lists)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    first_fwd_list.push_front(i);
    second_fwd_list.push_front(i);
  }
  out << (first_fwd_list != second_fwd_list);
  BOOST_TEST(out.str() == "0");
}

BOOST_AUTO_TEST_CASE(compare_two_not_equal_not_empty_lists_different_size)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    first_fwd_list.push_front(i);
    second_fwd_list.push_front(4 - i);
  }
  second_fwd_list.pop_front();
  out << (first_fwd_list != second_fwd_list);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(compare_two_not_equal_not_empty_lists_one_size)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first_fwd_list = {};
  petrov::ForwardRingList< int > second_fwd_list = {};
  for (int i = 1; i <= 3; i++)
  {
    first_fwd_list.push_front(i);
    second_fwd_list.push_front(4 - i);
  }
  out << (first_fwd_list != second_fwd_list);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(remove_if_method)

bool isEqualToOne(int number)
{
  return number == 1;
}

bool isEqualToFive(int number)
{
  return number == 5;
}

bool isEqualToSeven(int number)
{
  return number == 7;
}

BOOST_AUTO_TEST_CASE(remove_if_element_from_empty_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.remove_if(isEqualToOne);
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(remove_if_element_from_one_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.remove_if(isEqualToOne);
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

bool isLessThanTen(int number)
{
  return number < 10;
}

BOOST_AUTO_TEST_CASE(remove_if_element_from_list_filled_with_it)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 0; i < 10; i++)
  {
    fwd_list.push_front(1);
  }
  fwd_list.remove_if(isLessThanTen);
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(remove_if_element_from_list_which_are_not_there)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 2; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.remove_if(isEqualToOne);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2");
}

BOOST_AUTO_TEST_CASE(remove_if_element_from_start_of_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.reverse();
  fwd_list.remove_if(isEqualToOne);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "2 3 4 5 6 7 8 9 10");
}

BOOST_AUTO_TEST_CASE(remove_if_element_from_end_of_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.remove_if(isEqualToOne);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "10 9 8 7 6 5 4 3 2");
}

BOOST_AUTO_TEST_CASE(remove_if_elements_from_list_which_are_there)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  for (int i = 1; i <= 10; i++)
  {
    fwd_list.push_front(i);
  }
  fwd_list.remove_if(isEqualToFive);
  fwd_list.remove_if(isEqualToOne);
  fwd_list.remove_if(isEqualToSeven);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "10 9 8 6 4 3 2");
}

BOOST_AUTO_TEST_CASE(remove_if_elements_from_list_to_make_it_empty)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list = {};
  fwd_list.push_front(1);
  fwd_list.push_front(5);
  fwd_list.push_front(7);
  fwd_list.remove_if(isEqualToFive);
  fwd_list.remove_if(isEqualToSeven);
  fwd_list.remove_if(isEqualToOne);
  out << fwd_list.empty();
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(fill_constructor)

BOOST_AUTO_TEST_CASE(fill_with_one_element)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(1, 1);
  auto it = fwd_list.cbegin();
  out << *(it++);
  BOOST_TEST(out.str() == "1");
}

BOOST_AUTO_TEST_CASE(fill_with_three_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(3, 3);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "3 3 3");
}

BOOST_AUTO_TEST_CASE(fill_with_five_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(5, 5);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "5 5 5 5 5");
}

BOOST_AUTO_TEST_CASE(fill_with_seven_elements)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(7, 7);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  BOOST_TEST(out.str() == "7 7 7 7 7 7 7");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(splice_method_all_list)

BOOST_AUTO_TEST_CASE(splice_empty_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(7, 7);
  petrov::ForwardRingList< int > second;
  auto pos = first.begin();
  for (size_t i = 0; i < 6; i++)
  {
    ++pos;
  }
  first.splice(pos, second);
  auto it = first.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != first.cend());
  out << " " << second.empty();
  BOOST_TEST(out.str() == "7 7 7 7 7 7 7 1");
}

BOOST_AUTO_TEST_CASE(splice_to_one_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(1, 1);
  petrov::ForwardRingList< int > second(3, 3);
  auto pos = first.begin();
  first.splice(pos, second);
  auto it = first.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != first.cend());
  out << " " << *it;
  out << " " << second.empty();
  BOOST_TEST(out.str() == "1 3 3 3 1 1");
}

BOOST_AUTO_TEST_CASE(splice_not_empty_list_after_middle)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(7, 7);
  petrov::ForwardRingList< int > second(3, 3);
  auto pos = first.begin();
  for (size_t i = 0; i < 3; i++)
  {
    ++pos;
  }
  first.splice(pos, second);
  auto it = first.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != first.cend());
  out << " " << second.empty();
  BOOST_TEST(out.str() == "7 7 7 7 3 3 3 7 7 7 1");
}

BOOST_AUTO_TEST_CASE(splice_not_empty_list_after_head)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(7, 7);
  petrov::ForwardRingList< int > second(3, 3);
  auto pos = first.begin();
  first.splice(pos, second);
  auto it = first.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != first.cend());
  out << " " << second.empty();
  BOOST_TEST(out.str() == "7 3 3 3 7 7 7 7 7 7 1");
}

BOOST_AUTO_TEST_CASE(splice_not_empty_list_after_tail)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(7, 7);
  first.push_front(5);
  petrov::ForwardRingList< int > second(3, 3);
  auto pos = first.end();
  first.splice(pos, second);
  auto it = first.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != first.cend());
  out << " " << *it;
  out << " " << second.empty() << " " << first.size();
  BOOST_TEST(out.str() == "5 7 7 7 7 7 7 7 3 3 3 5 1 11");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(splice_method_one_node)

BOOST_AUTO_TEST_CASE(splice_node_to_middle)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(7, 7);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 3; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto it = second.begin();
  first.splice(pos, second, it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2; 
  }
  while (it_2++ != second.cend());
  BOOST_TEST(out.str() == "7 7 2 7 7 7 7 7 1 3");
}

BOOST_AUTO_TEST_CASE(splice_to_one_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(1, 1);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 3; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  auto it = second.begin();
  first.splice(pos, second, it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2; 
  }
  while (it_2++ != second.cend());
  BOOST_TEST(out.str() == "1 2 1 1 3");
}

BOOST_AUTO_TEST_CASE(splice_node_after_head)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(7, 7);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 3; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  auto it = second.begin();
  first.splice(pos, second, it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2; 
  }
  while (it_2++ != second.cend());
  BOOST_TEST(out.str() == "7 2 7 7 7 7 7 7 1 3");
}

BOOST_AUTO_TEST_CASE(splice_node_after_tail)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(7, 7);
  first.push_front(5);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 3; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  for (size_t i = 0; i < 7; i++)
  {
    ++pos;
  }
  auto it = second.begin();
  first.splice(pos, first, it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2; 
  }
  while (it_2++ != second.cend());
  BOOST_TEST(out.str() == "5 7 7 7 7 7 7 7 2 5 1 3");
}

BOOST_AUTO_TEST_CASE(splice_node_from_tail)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 4);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 3; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  auto it = second.begin();
  ++it;
  first.splice(pos, second, it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2; 
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "4 3 4 4 1 2 1");
}

BOOST_AUTO_TEST_CASE(splice_node_from_head)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 4);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 3; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  auto it = second.begin();
  ++it;
  ++it;
  first.splice(pos, second, it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2; 
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "4 1 4 4 2 3 2");
}

BOOST_AUTO_TEST_CASE(splice_node_from_one_element_list)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 4);
  petrov::ForwardRingList< int > second(1, 5);
  second.reverse();
  auto pos = first.begin();
  auto it = second.begin();
  first.splice(pos, second, it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << second.empty();
  BOOST_TEST(out.str() == "4 5 4 4 1");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(splice_method_range)

BOOST_AUTO_TEST_CASE(first_eq_last_middle)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(1, 1);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  auto it = second.begin();
  ++it;
  ++it;
  auto first_it = it;
  auto last_it = it;
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++) << " " << *(it_2++) << " " << second.size();
  BOOST_TEST(out.str() == "1 4 5 1 2 1 3 3 1");
}

BOOST_AUTO_TEST_CASE(first_eq_last_begin)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(2, 1);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto it = second.begin();
  auto first_it = it;
  auto last_it = it;
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++) << " " << *(it_2++);
  BOOST_TEST(out.str() == "1 1 2 3 4 5 1 1 1");
}

BOOST_AUTO_TEST_CASE(first_eq_last_end)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  ++pos;
  auto it = second.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  auto first_it = it;
  auto last_it = it;
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++) << " " << *(it_2++);
  BOOST_TEST(out.str() == "10 10 10 1 2 3 4 10 5 5");
}

BOOST_AUTO_TEST_CASE(splice_one_el_btw)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto first_it = second.begin();
  auto it = second.begin();
  ++it;
  ++it;
  auto last_it = it;
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2;
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "10 10 2 10 10 1 3 4 5 1");
}

BOOST_AUTO_TEST_CASE(splice_three_el_btw)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto first_it = second.begin();
  auto last_it = second.end();
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2;
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "10 10 2 3 4 10 10 1 5 1");
}

BOOST_AUTO_TEST_CASE(splice_three_el_end)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto last_it = second.begin();
  auto first_it = second.begin();
  ++first_it;
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2;
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "10 10 3 4 5 10 10 1 2 1");
}

BOOST_AUTO_TEST_CASE(splice_three_el_begin)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto last_it = second.begin();
  ++last_it;
  ++last_it;
  ++last_it;
  auto first_it = second.end();
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2;
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "10 10 1 2 3 10 10 4 5 4");
}

BOOST_AUTO_TEST_CASE(splice_with_cycle_two)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto last_it = second.begin();
  ++last_it;
  auto first_it = second.begin();
  ++first_it;
  ++first_it;
  ++first_it;
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2;
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "10 10 5 1 10 10 2 3 4 2");
}

BOOST_AUTO_TEST_CASE(splice_one_btw)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto first_it = ++second.begin();
  auto last_it = second.begin();
  ++last_it;
  ++last_it;
  ++last_it;
  first.splice(pos, second, first_it, last_it);
  auto it_1 = first.cbegin();
  out << *(it_1++);
  do
  {
    out << " " << *it_1;
  }
  while (it_1++ != first.cend());
  out << " " << *it_1;
  auto it_2 = second.cbegin();
  out << " " << *(it_2++);
  do
  {
    out << " " << *it_2;
  }
  while (it_2++ != second.cend());
  out << " " << *it_2;
  BOOST_TEST(out.str() == "10 10 3 10 10 1 2 4 5 1");
}

BOOST_AUTO_TEST_CASE(splice_with_cycle_two_size_test)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > first(3, 10);
  petrov::ForwardRingList< int > second;
  for (int i = 1; i <= 5; i++)
  {
    second.push_front(i);
  }
  second.reverse();
  auto pos = first.begin();
  ++pos;
  auto last_it = second.begin();
  ++last_it;
  auto first_it = second.begin();
  ++first_it;
  ++first_it;
  ++first_it;
  first.splice(pos, second, first_it, last_it);
  out << first.size() << " " << second.size();
  BOOST_TEST(out.str() == "5 3");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(assign_method)

BOOST_AUTO_TEST_CASE(assign_one)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(5, 5);
  fwd_list.assign(1, 1);
  auto it = fwd_list.cbegin();
  out << *(it++) << " " << *(it++) << " " << *it << " " << fwd_list.size();
  BOOST_TEST(out.str() == "1 1 1 1");
}

BOOST_AUTO_TEST_CASE(assign_two)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(5, 5);
  fwd_list.assign(2, 2);
  auto it = fwd_list.cbegin();
  out << *(it++) << " " << *(it++) << " " << *it << " " << fwd_list.size();
  BOOST_TEST(out.str() == "2 2 2 2");
}

BOOST_AUTO_TEST_CASE(assign_five)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(5, 5);
  fwd_list.assign(5, 10);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  out << " " << *it << " " << fwd_list.size();
  BOOST_TEST(out.str() == "10 10 10 10 10 10 5");
}

BOOST_AUTO_TEST_CASE(assign_seven)
{
  std::ostringstream out;
  petrov::ForwardRingList< int > fwd_list(5, 5);
  fwd_list.assign(7, 5);
  auto it = fwd_list.cbegin();
  out << *(it++);
  do
  {
    out << " " << *it;
  }
  while (it++ != fwd_list.cend());
  out << " " << *it << " " << fwd_list.size();
  BOOST_TEST(out.str() == "5 5 5 5 5 5 5 5 7");
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()




#include <boost/test/unit_test.hpp>
#include "fwd_list/definition.hpp"

BOOST_AUTO_TEST_SUITE(constructors_tests)
BOOST_AUTO_TEST_CASE(default_constructor_test)
{
  maslevtsov::FwdList< int > list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
  maslevtsov::FwdList< int > list1;
  maslevtsov::FwdList< int > list2(list1);
  BOOST_TEST(list2.empty());
  list1.push_front(0);
  maslevtsov::FwdList< int > list3(list1);
  BOOST_TEST(list3.front() == 0);
  BOOST_TEST(list3.size() == 1);
  list1.push_front(1);
  maslevtsov::FwdList< int > list4(list1);
  BOOST_TEST(list4.front() == 1);
  BOOST_TEST(list4.back() == 0);
  BOOST_TEST(list4.size() == 2);
}

BOOST_AUTO_TEST_CASE(move_constructor_test)
{
  maslevtsov::FwdList< int > list1 = {0, 1};
  maslevtsov::FwdList< int > list2(std::move(list1));
  BOOST_TEST(list2.front() == 0);
  BOOST_TEST(list2.back() == 1);
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(fill_constructor_test)
{
  maslevtsov::FwdList< char > list1(0, 'r');
  BOOST_TEST(list1.empty());
  maslevtsov::FwdList< char > list2(2, 'r');
  BOOST_TEST(list2.front() == 'r');
  BOOST_TEST(list2.back() == 'r');
  BOOST_TEST(list2.size() == 2);
}

BOOST_AUTO_TEST_CASE(range_constructor_test)
{
  maslevtsov::FwdList< char > list1 = {'k', 'e', 'k'};
  maslevtsov::FwdList< int > list2(list1.begin(), list1.begin());
  BOOST_TEST(list2.empty());
  maslevtsov::FwdList< int > list3(++list1.begin(), list1.end());
  BOOST_TEST(list3.front() == 'e');
  BOOST_TEST(list3.back() == 'k');
  BOOST_TEST(list3.size() == 2);
}

BOOST_AUTO_TEST_CASE(initializer_list_constructor_test)
{
  maslevtsov::FwdList< int > list = {0, 1};
  BOOST_TEST(list.front() == 0);
  BOOST_TEST(list.back() == 1);
  BOOST_TEST(list.size() == 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(assignment_operators_tests)
BOOST_AUTO_TEST_CASE(copy_assignment_operator_test)
{
  maslevtsov::FwdList< int > list1 = {0, 1};
  maslevtsov::FwdList< int > list2;
  list2 = list1;
  BOOST_TEST(list2.front() == 0);
  BOOST_TEST(list2.back() == 1);
  BOOST_TEST(list2.size() == 2);
}

BOOST_AUTO_TEST_CASE(move_assignment_operator_test)
{
  maslevtsov::FwdList< int > list1 = {0, 1};
  maslevtsov::FwdList< int > list2;
  list2 = std::move(list1);
  BOOST_TEST(list2.front() == 0);
  BOOST_TEST(list2.back() == 1);
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(initializer_list_assignment_operator_test)
{
  maslevtsov::FwdList< int > list;
  list = {0, 1};
  BOOST_TEST(list.front() == 0);
  BOOST_TEST(list.back() == 1);
  BOOST_TEST(list.size() == 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(assign_tests)
BOOST_AUTO_TEST_CASE(fill_assign_test)
{
  maslevtsov::FwdList< char > list;
  list.assign(2, 'r');
  BOOST_TEST(list.front() == 'r');
  BOOST_TEST(list.back() == 'r');
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(range_assign_test)
{
  maslevtsov::FwdList< char > list1 = {'u', 'w', 'u'};
  maslevtsov::FwdList< char > list2;
  list2.assign(++list1.begin(), list1.end());
  BOOST_TEST(list2.front() == 'w');
  BOOST_TEST(list2.back() == 'u');
  BOOST_TEST(list2.size() == 2);
}

BOOST_AUTO_TEST_CASE(initializer_list_assign_test)
{
  maslevtsov::FwdList< char > list;
  list.assign({'r', 'r'});
  BOOST_TEST(list.front() == 'r');
  BOOST_TEST(list.back() == 'r');
  BOOST_TEST(list.size() == 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(element_access_tests)
BOOST_AUTO_TEST_CASE(front_test)
{
  maslevtsov::FwdList< int > list = {0, 1};
  BOOST_TEST(list.front() == 0);
}

BOOST_AUTO_TEST_CASE(back_test)
{
  maslevtsov::FwdList< int > list = {0, 1};
  BOOST_TEST(list.back() == 1);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(iterators_tests)
BOOST_AUTO_TEST_CASE(begin_test)
{
  maslevtsov::FwdList< int > list = {0, 1};
  auto it = list.begin();
  auto c_it = list.cbegin();
  BOOST_TEST(*it == 0);
  BOOST_TEST(*c_it == 0);
}

BOOST_AUTO_TEST_CASE(end_test)
{
  maslevtsov::FwdList< int > list = {0, 1};
  auto it = list.end();
  auto c_it = list.cend();
  BOOST_TEST(*it == 0);
  BOOST_TEST(*c_it == 0);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(capacity_tests)
BOOST_AUTO_TEST_CASE(size_test)
{
  maslevtsov::FwdList< int > list = {0, 1};
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(empty_test)
{
  maslevtsov::FwdList< int > list;
  BOOST_TEST(list.empty());
  list.push_front(0);
  BOOST_TEST(!list.empty());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(modifiers_tests)
BOOST_AUTO_TEST_CASE(push_front_test)
{
  maslevtsov::FwdList< int > list;
  list.push_front(0);
  list.push_front(1);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 0);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(push_back_test)
{
  maslevtsov::FwdList< int > list;
  list.push_back(0);
  list.push_back(1);
  BOOST_TEST(list.front() == 0);
  BOOST_TEST(list.back() == 1);
  BOOST_TEST(list.size() == 2);
}

BOOST_AUTO_TEST_CASE(pop_front_test)
{
  maslevtsov::FwdList< int > list = {0, 1};
  list.pop_front();
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.size() == 1);
  list.pop_front();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap_test)
{
  maslevtsov::FwdList< int > list1 = {0};
  maslevtsov::FwdList< int > list2 = {1, 2};
  list1.swap(list2);
  BOOST_TEST(list1.front() == 1);
  BOOST_TEST(list1.back() == 2);
  BOOST_TEST(list1.size() == 2);
  BOOST_TEST(list2.front() == 0);
  BOOST_TEST(list2.size() == 1);
}

BOOST_AUTO_TEST_CASE(clear_test)
{
  maslevtsov::FwdList< int > list;
  list.clear();
  BOOST_TEST(list.empty());
  list.push_front(0);
  list.clear();
  BOOST_TEST(list.empty());
}
BOOST_AUTO_TEST_SUITE_END()

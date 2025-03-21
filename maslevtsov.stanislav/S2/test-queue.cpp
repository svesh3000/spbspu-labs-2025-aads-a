#include <boost/test/unit_test.hpp>
#include "queue.hpp"

BOOST_AUTO_TEST_SUITE(constructors_tests)
BOOST_AUTO_TEST_CASE(default_constructor_test)
{
  maslevtsov::Queue< int > q;
  BOOST_TEST(q.empty());
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
  maslevtsov::Queue< int > q1;
  q1.push(1);
  q1.push(2);
  maslevtsov::Queue< int > q2(q1);
  BOOST_TEST(q1.front() == q2.front());
  BOOST_TEST(q1.back() == q2.back());
  BOOST_TEST(q1.size() == q2.size());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operators_tests)
BOOST_AUTO_TEST_CASE(copy_assignment_operator_test)
{
  maslevtsov::Queue< int > q1;
  q1.push(1);
  q1.push(2);
  maslevtsov::Queue< int > q2;
  q2 = q1;
  BOOST_TEST(q1.front() == q2.front());
  BOOST_TEST(q1.back() == q2.back());
  BOOST_TEST(q1.size() == q2.size());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(elements_access_tests)
BOOST_AUTO_TEST_CASE(front_test)
{
  maslevtsov::Queue< int > q1;
  q1.push(1);
  q1.push(2);
  BOOST_TEST(q1.front() == 1);
}

BOOST_AUTO_TEST_CASE(back_test)
{
  maslevtsov::Queue< int > q1;
  q1.push(1);
  q1.push(2);
  BOOST_TEST(q1.back() == 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(capacity_tests)
BOOST_AUTO_TEST_CASE(empty_test)
{
  maslevtsov::Queue< int > q1;
  BOOST_TEST(q1.empty());
  q1.push(1);
  BOOST_TEST(!q1.empty());
}

BOOST_AUTO_TEST_CASE(size_test)
{
  maslevtsov::Queue< int > q1;
  q1.push(1);
  BOOST_TEST(q1.size() == 1);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(modifiers_tests)
BOOST_AUTO_TEST_CASE(push_test)
{
  maslevtsov::Queue< int > q1;
  q1.push(1);
  BOOST_TEST(q1.front() == 1);
  BOOST_TEST(q1.size() == 1);
  int n = 2;
  q1.push(n);
  BOOST_TEST(q1.back() == 2);
  BOOST_TEST(q1.size() == 2);
}

BOOST_AUTO_TEST_CASE(pop_test)
{
  maslevtsov::Queue< int > q1;
  q1.push(1);
  q1.push(2);
  q1.pop();
  BOOST_TEST(q1.size() == 1);
  BOOST_TEST(q1.front() == 2);
  q1.pop();
  BOOST_TEST(q1.empty());
}
BOOST_AUTO_TEST_SUITE_END()

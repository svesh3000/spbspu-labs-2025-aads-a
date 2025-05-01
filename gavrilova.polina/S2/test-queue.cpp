#include <boost/test/unit_test.hpp>
#include "Queue.hpp"
#include <iostream>
BOOST_AUTO_TEST_CASE(test_element_access_queue)
{
  gavrilova::Queue< int > queue{};
  queue.push(1);
  queue.push(2);
  queue.push(1 + 2);
  BOOST_TEST(queue.front() == 1);
}

BOOST_AUTO_TEST_CASE(test_constructors_queue)
{
  gavrilova::Queue< int > queue1{};
  queue1.push(1);
  queue1.push(2);
  queue1.push(1 + 2);
  gavrilova::Queue< int > queue2 = queue1;
  BOOST_TEST(queue1.front() == 1);
  BOOST_TEST(queue1.size() == queue2.size());
}

BOOST_AUTO_TEST_CASE(test_assignment_operators_queue)
{
  gavrilova::Queue< int > queue1;
  queue1.push(1);
  queue1.push(2);
  queue1.push(1 + 2);
  gavrilova::Queue< int > queue2;
  queue2 = queue1;
  BOOST_TEST(queue1.front() == 1);
  BOOST_TEST(queue2.front() == 1);
  BOOST_TEST(queue1.size() == queue2.size());
}

BOOST_AUTO_TEST_CASE(test_pop_queue)
{
  gavrilova::Queue< int > queue;
  queue.push(1);
  queue.push(2);
  queue.push(1 + 2);
  queue.pop();
  BOOST_TEST(queue.front() == 2);
  queue.pop();
  BOOST_TEST(queue.front() == 3);
}

#include <boost/test/unit_test.hpp>
#include "stack.hpp"

BOOST_AUTO_TEST_CASE(test_capacity_stack)
{
  karnauhova::Stack< int > stack;
  BOOST_TEST(stack.empty() == true);
  BOOST_TEST(stack.size() == 0);
  stack.push(2);
  BOOST_TEST(stack.size() == 1);
}

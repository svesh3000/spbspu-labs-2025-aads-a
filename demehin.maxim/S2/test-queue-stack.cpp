#include <boost/test/unit_test.hpp>
#include <sstream>
#include <stack.hpp>

BOOST_AUTO_TEST_CASE(stack_test)
{
  demehin::Stack< int > stack;
  BOOST_TEST(stack.size() == 0);
  BOOST_TEST(stack.empty());

  stack.push(1);
  stack.push(2);
  BOOST_TEST(stack.size() == 2);
  BOOST_TEST(!stack.empty());
  BOOST_TEST(stack.top() == 2);

  stack.pop();
  BOOST_TEST(stack.size() == 1);
  BOOST_TEST(stack.top() == 1);
}

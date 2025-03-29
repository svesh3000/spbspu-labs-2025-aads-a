#include <boost/test/unit_test.hpp>
#include "postfix_token.hpp"

BOOST_AUTO_TEST_SUITE(postfix_token_constructor_tests)
BOOST_AUTO_TEST_CASE(convert_constructor_test)
{
  maslevtsov::PostfixToken exp1("1 + 1");
  BOOST_TEST(exp1() == 2);
  try {
    maslevtsov::PostfixToken exp2("1 + 1 )");
  } catch (const std::logic_error&) {
    BOOST_TEST(true);
  }
}
BOOST_AUTO_TEST_SUITE_END()

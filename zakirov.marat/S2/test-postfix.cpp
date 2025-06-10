#include <boost/test/unit_test.hpp>
#include "postfix.hpp"

BOOST_AUTO_TEST_CASE(string_constructor_postfix)
{
  zakirov::Postfix postfix_t("1 + 1");
  BOOST_TEST(postfix_t() == 2);
}


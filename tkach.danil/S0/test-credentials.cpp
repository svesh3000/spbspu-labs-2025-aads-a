#include <boost/test/unit_test.hpp>
#include <sstream>
#include "credentials.hpp"

BOOST_AUTO_TEST_CASE(credentialTest)
{
  std::ostringstream out;
  tkach::outCredentials(out);
  BOOST_TEST(out.str() == "tkach.danil");
}


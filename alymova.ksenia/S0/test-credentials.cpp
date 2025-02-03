#include <boost/test/unit_test.hpp>
#include <sstream>
#include "test-credentials.hpp"

BOOST_AUTO_TEST_CASE(credentials_test)
{
  std::ostringstream out;
  alymova::out_credentials(out);
  BOOST_TEST(out.str() == "alymova.ksenia");
}


#include <sstream>
#include <string>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include "tree.hpp"
#include "keySum.hpp"

using namespace kiselev;

BOOST_AUTO_TEST_SUITE(traverse)

BOOST_AUTO_TEST_CASE(lnr)
{
  RBTree< int, std::string > tree({ { 10, "a" }, { 7, "b" }, { 15, "c" }, { 5, "d" }, { 8, "e" } });
  std::ostringstream iss;
  KeySum fun;
  fun = tree.traverse_lnr(fun);
  iss << fun.sum << fun.str;
  BOOST_TEST(iss.str() == "45 d b e a c");
}

BOOST_AUTO_TEST_SUITE_END();

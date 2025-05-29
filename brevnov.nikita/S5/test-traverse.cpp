#include <sstream>
#include <string>
#include <boost/test/tools/interface.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>
#include "tree.hpp"
#include "keySum.hpp"

using namespace brevnov;

BOOST_AUTO_TEST_CASE(traverse)
{
  RBTree< int, std::string > tree({ { 10, "a" }, { 43, "b" }, { 25, "c" }, { 48, "d" }, { 9, "e" } });
  std::ostringstream iss;
  KeySum funLnr;
  funLnr = tree.traverse_lnr(funLnr);
  iss << funLnr.sum << funLnr.str;
  BOOST_TEST(iss.str() == "135 e a c b d");
  KeySum funRnl;
  funRnl = tree.traverse_rnl(funRnl);
  iss.str("");
  iss << funRnl.sum << funRnl.str;
  BOOST_TEST(iss.str() == "135 d b c a e");
  iss.str("");
  KeySum funBr;
  funBreadth = tree.traverse_breadth(funBr);
  iss << funBr.sum << funBr.str;
  BOOST_TEST(iss.str() == "135 a b c d e");
}

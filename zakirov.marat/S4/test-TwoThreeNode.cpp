#include <boost/test/unit_test.hpp>
#include "TwoThreeNode.hpp"

BOOST_AUTO_TEST_CASE(constructor)
{
  zakirov::TwoThreeNode< int > test_node(5, 1);
  BOOST_TEST(test_node.data_ == 5);
  BOOST_TEST(test_node.key_ == 1);
}

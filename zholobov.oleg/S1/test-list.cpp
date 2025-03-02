#include <boost/test/unit_test.hpp>

#include <sstream>

#include "CircularFwdList.hpp"
#include "CircularFwdListIterators.hpp"

using test_type = zholobov::CircularFwdList< int >;

std::ostream& operator<<(std::ostream& out, const test_type& list)
{
  for (auto it = list.begin(); it != list.end(); ++it) {
    out << *it << " ";
  }
  return out;
}

BOOST_AUTO_TEST_CASE(basic_list_tests)
{
  test_type list;
  list.push_front(13);
  list.push_front(42);
  BOOST_TEST(list.size() == 2);

  std::stringstream ss;
  ss << list;
  BOOST_TEST(ss.str() == "42 13 ");
}

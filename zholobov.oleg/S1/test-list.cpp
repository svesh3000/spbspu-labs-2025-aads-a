#include <boost/test/unit_test.hpp>

#include <sstream>

#include "CircularFwdList.hpp"
#include "CircularFwdListIterators.hpp"

using test_type = zholobov::CircularFwdList< int >;

size_t list_length(const test_type& list)
{
  size_t result = 0;
  for (auto it = list.begin(); it != list.end(); ++it) {
    ++result;
  }
  return result;
}

std::ostream& list_out(std::ostream& out, const test_type& list)
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
  list_out(ss, list);
  BOOST_TEST(ss.str() == "42 13 ");
}

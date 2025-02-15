#include <boost/test/unit_test.hpp>
#include <list/list.hpp>

BOOST_AUTO_TEST_CASE(list_test)
{
  demehin::List< int > list;
  BOOST_TEST(list.size() == 0);
}

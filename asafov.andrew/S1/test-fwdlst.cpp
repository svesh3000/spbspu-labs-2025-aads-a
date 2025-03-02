#include <boost/test/unit_test.hpp>
#include "fwdlst4d.hpp"

BOOST_AUTO_TEST_CASE(cbegin_test)
{
  asafov::Forward_list<int> list;
  list.push_back(0);
  list.push_back(1);
  auto it = list.cbegin();
  BOOST_TEST(*it == list.front());
}

BOOST_AUTO_TEST_CASE(cend_test)
{
  asafov::Forward_list<int> list;
  list.push_back(0);
  list.push_back(1);
  auto it = list.cend();
  ++it;
  BOOST_TEST(*it == list.front());
}

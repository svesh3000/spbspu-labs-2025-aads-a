#include <boost/test/unit_test.hpp>
#include "fwd_list.hpp"

BOOST_AUTO_TEST_CASE(begin_test)
{
  maslevtsov::FwdList< int > list;
  list.push_front(0);
  list.push_front(1);
  maslevtsov::FwdIterator< int > iterator = list.begin();
  BOOST_TEST(*iterator == 1);
}

BOOST_AUTO_TEST_CASE(end_test)
{
  maslevtsov::FwdList< int > list;
  list.push_front(0);
  list.push_front(1);
  maslevtsov::FwdIterator< int > iterator = list.end();
  BOOST_TEST(*iterator == 0);
}

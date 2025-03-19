#include <boost/test/unit_test.hpp>
#include "fwdlist-ring.hpp"

BOOST_AUTO_TEST_SUITE(constructors)
BOOST_AUTO_TEST_CASE(default_constructor)
{
  sveshnikov::FwdList< int > list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  sveshnikov::FwdList< int > list;
  sveshnikov::FwdList< int > list_copy = list;
  BOOST_TEST(list_copy.empty());
  list.push_back(1);
  sveshnikov::FwdList< int > list_copy2 = list;
  BOOST_TEST(list_copy2.front() == 1);
  list.push_back(2);
  sveshnikov::FwdList< int > list_copy3 = list;
  BOOST_TEST(list_copy3.getSize() == 2);
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  sveshnikov::FwdList< int > list_copy = std::move(list);
  BOOST_TEST(list_copy.getSize() == 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(interface)
BOOST_AUTO_TEST_CASE(iterators)
{
  sveshnikov::FwdList< int > list;
  list.push_back(1);
  list.push_back(2);
  BOOST_TEST(*list.begin() == 1);
  BOOST_TEST(*list.cbegin() == 1);

  BOOST_TEST(*list.end() == 1);
  BOOST_TEST(*list.cend() == 1);

  BOOST_TEST(*list.before_begin() == 2);
  BOOST_TEST(*list.cbefore_begin() == 2);
}

BOOST_AUTO_TEST_SUITE_END()

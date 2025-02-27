#include <boost/test/unit_test.hpp>
#include "list.hpp"
#include "iterators.hpp"
#include "listNode.hpp"

using list_t = alymova::List< int >;
using iter_t = alymova::Iterator< int >;
BOOST_AUTO_TEST_CASE(test_constructors_operators)
{
  list_t list1 = {3, 1};
  list_t list2(list1);
  BOOST_TEST(list1 == list2);

  list_t list3(std::move(list_t{3, 1}));
  BOOST_TEST(list1 == list3);

  list_t list4 = {5, 2};
  list3 = list4;
  BOOST_TEST(list3 == list4);

  list4 = list_t{3, 1};
  BOOST_TEST(list4 == list1);
}
BOOST_AUTO_TEST_CASE(test_list_iterators)
{
  list_t list = {3, 1};
  iter_t iter_b = list.begin();
  iter_t iter_e = list.end();
  BOOST_TEST(*iter_b == 1);
  BOOST_TEST(*iter_e-- == 0);
}
#include "test_utils.hpp"

BOOST_AUTO_TEST_SUITE(S1_erasors_test)

BOOST_AUTO_TEST_CASE(erase_single_test)
{
  rychkov::List< int > list = {3, 6, 4, -1, 7};
  BOOST_TEST(*list.erase(++list.begin()) == 4);
  rychkov::fullCompare(list, {3, 4, -1, 7});
}
BOOST_AUTO_TEST_CASE(erase_multiple_test)
{
  rychkov::List< int > list = {3, 6, 4, -1, 7};
  BOOST_TEST(*list.erase(list.begin(), ++(++list.begin())) == 4);
  rychkov::fullCompare(list, {4, -1, 7});
}
BOOST_AUTO_TEST_CASE(remove_test)
{
  rychkov::List< int > list = {3, 3, 4, -1, 3, 7, 3};
  BOOST_TEST(list.remove(3) == 4);
  rychkov::fullCompare(list, {4, -1, 7});
}

BOOST_AUTO_TEST_CASE(splice_all_lvalue_test)
{
  rychkov::List< int > list1 = {3, 7, 1, 0};
  rychkov::List< int > list2;
  list2.splice(list2.begin(), list1);
  rychkov::fullCompare(list1, {});
  rychkov::fullCompare(list2, {3, 7, 1, 0});
}
BOOST_AUTO_TEST_CASE(splice_all_rvalue_test)
{
  rychkov::List< int > list;
  list.splice(list.begin(), {3, 7, 1, 0});
  rychkov::fullCompare(list, {3, 7, 1, 0});
}
BOOST_AUTO_TEST_CASE(splice_part_empty_test)
{
  rychkov::List< int > list1 = {3, 7, 1, 0};
  rychkov::List< int > list2;
  list2.splice(list2.begin(), list1, list1.begin(), ++(++list1.begin()));
  rychkov::fullCompare(list1, {1, 0});
  rychkov::fullCompare(list2, {3, 7});
}
BOOST_AUTO_TEST_CASE(splice_part_inner_test)
{
  rychkov::List< int > list1 = {3, 7, 1, 0};
  rychkov::List< int > list2 = {2, 4};
  list2.splice(++list2.begin(), list1, list1.begin(), ++(++list1.begin()));
  rychkov::fullCompare(list1, {1, 0});
  rychkov::fullCompare(list2, {2, 3, 7, 4});
}

BOOST_AUTO_TEST_SUITE_END()

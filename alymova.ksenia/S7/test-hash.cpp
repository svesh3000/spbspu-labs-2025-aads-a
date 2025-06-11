#include <boost/test/unit_test.hpp>
#include "hash-table.hpp"

BOOST_AUTO_TEST_CASE(test_constructors_operators)
{
  using Map = alymova::HashTable< int, std::string >;

  Map table1;
  BOOST_TEST(table1.empty());

  Map table2(table1);
  BOOST_TEST(table2.empty());

  table1.emplace(1, "cat");
  Map table3(table1);
  BOOST_TEST(table3.size() == 1);
  BOOST_TEST(table3.begin()->first == 1);

  Map table4(std::move(table3));
  BOOST_TEST(table4.size() == 1);
  BOOST_TEST(table4.begin()->second == "cat");
  BOOST_TEST(table3.size() == 0);

  Map table5(table4.begin(), table4.end());
  BOOST_TEST(table5.size() == 1);
  BOOST_TEST(table5.begin()->second == "cat");

  Map table6({{2, "d"}, {3, "p"}});
  BOOST_TEST(table6.size() == 2);
  BOOST_TEST(table6.begin()->second == "d");

  table1 = table6;
  BOOST_TEST(table1.size() == 2);
  BOOST_TEST(table1.begin()->second == "d");

  table1 = Map({{1, "ccc"}, {2, "ddd"}, {3, "ppp"}});
  BOOST_TEST(table1.size() == 3);
  BOOST_TEST(table1.begin()->second == "ccc");
}

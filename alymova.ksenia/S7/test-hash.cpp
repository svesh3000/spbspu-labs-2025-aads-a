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
BOOST_AUTO_TEST_CASE(test_iterators_size)
{
  using Map = alymova::HashTable< int, std::string >;

  Map table1;
  BOOST_TEST((table1.begin() == table1.end()));
  BOOST_TEST(table1.empty());
  BOOST_TEST(table1.size() == 0);

  std::pair< int, std::string >p(1, "a");
  table1.insert(p);
  auto it = table1.begin();
  BOOST_TEST((*it == p));
  BOOST_TEST(it->first == 1);
  BOOST_TEST(!table1.empty());
  BOOST_TEST(table1.size() == 1);

  ++it;
  BOOST_TEST((it == table1.end()));

  const Map table2;
  BOOST_TEST((table2.begin() == table2.end()));
  BOOST_TEST((table2.begin() == table2.cbegin()));
}
BOOST_AUTO_TEST_CASE(test_load_factor_rehash)
{
  using Map = alymova::HashTable< int, std::string >;

  Map table1;
  BOOST_TEST(table1.load_factor() == 0.0f);
  BOOST_TEST(table1.max_load_factor() == 0.7f);

  for (size_t i = 0; i < 6; i++)
  {
    table1.emplace(i, "aaa");
  }
  BOOST_TEST(table1.load_factor() > 0.5f);

  table1.max_load_factor(0.8f);
  BOOST_TEST(table1.max_load_factor() == 0.8f);

  table1.max_load_factor(0.5f);
  BOOST_TEST(table1.max_load_factor() == 0.5f);
  BOOST_TEST(table1.load_factor() < 0.5f);
  BOOST_TEST(table1.size() == 6);

  Map table2;
  table2.rehash();
  BOOST_TEST(table2.empty());
}
BOOST_AUTO_TEST_CASE(test_insert_emplace)
{
  using Map = alymova::HashTable< int, std::string >;

  Map table1;
  table1.emplace(1, "aaa");
  BOOST_TEST(table1.size() == 1);
  BOOST_TEST(table1.begin()->first == 1);

  table1.emplace(1, "bbb");
  BOOST_TEST(table1.size() == 2);
  BOOST_TEST(table1.begin()->second == "aaa");

  table1.emplace(3, "ccc");
  table1.emplace(1, "ddd");
  BOOST_TEST(table1.size() == 4);

  table1.emplace(10, "fff");
  table1.emplace(10, "rrr");
  BOOST_TEST(table1.size() == 6);
  BOOST_TEST(table1.begin()->first == 10);
  BOOST_TEST(table1.begin()->second == "rrr");

  table1.erase(1);
  table1.emplace(9, "lll");
  table1.emplace(9, "jjj");
  table1.emplace(9, "iii");
  BOOST_TEST(table1.size() == 6);
  BOOST_TEST(table1.begin()->first == 9);
  BOOST_TEST(table1.begin()->second == "iii");

  table1.emplace(4, "www");
  table1.emplace(5, "ttt");
  BOOST_TEST(table1.size() == 8);
  BOOST_TEST(table1.load_factor() < 0.4f);
}

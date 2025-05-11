#include <boost/test/unit_test.hpp>
#include "hash_table.hpp"

BOOST_AUTO_TEST_CASE(table_test)
{
  demehin::HashTable< int, std::string > table;

  table[1] = "one";
  table[5] = "five";
  table[3] = "three";

  BOOST_TEST(table.size() == 3);
  BOOST_TEST(table[5] == "five");
  BOOST_TEST(table.find(3)->second == "three");
}

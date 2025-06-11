#include <boost/test/unit_test.hpp>
#include <sstream>
#include "hashTable.hpp"

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  maslov::HashTable< int, std::string > hashTable(20);
  BOOST_TEST(hashTable.empty());
  BOOST_TEST(hashTable.size() == 0);
  BOOST_TEST(hashTable.loadFactor() == 0.0f);
}

BOOST_AUTO_TEST_CASE(insert)
{
  maslov::HashTable< int, std::string > table(10);
  auto res1 = table.insert(1, "one");
  BOOST_TEST(res1.second == true);
  BOOST_TEST(res1.first->second == "one");
  BOOST_TEST(table.size() == 1);
  auto res2 = table.insert(2, "two");
  BOOST_TEST(res2.second == true);
  BOOST_TEST(table.size() == 2);
  auto res3 = table.insert(1, "uno");
  BOOST_TEST(res3.second == false);
  BOOST_TEST(res3.first->second == "one");
  BOOST_TEST(table.size() == 2);
}

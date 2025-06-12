#include <boost/test/unit_test.hpp>
#include <sstream>
#include "hashTable.hpp"

BOOST_AUTO_TEST_SUITE(constructors)

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  maslov::HashTable< int, std::string > hashTable;
  BOOST_TEST(hashTable.empty());
  BOOST_TEST(hashTable.size() == 0);
  BOOST_TEST(hashTable.loadFactor() == 0.0f);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(insert)
{
  maslov::HashTable< int, std::string > hashTable;
  auto it1 = hashTable.insert(1, "one");
  BOOST_TEST(it1.second == true);
  BOOST_TEST(it1.first->second == "one");
  BOOST_TEST(hashTable.size() == 1);

  auto it2 = hashTable.insert(2, "two");
  BOOST_TEST(it2.second == true);
  BOOST_TEST(hashTable.size() == 2);

  auto it3 = hashTable.insert(1, "first");
  BOOST_TEST(it3.second == false);
  BOOST_TEST(it3.first->second == "one");
  BOOST_TEST(hashTable.size() == 2);
}

BOOST_AUTO_TEST_CASE(insertRehash)
{
  maslov::HashTable< int, std::string > hashTable(2);
  hashTable.insert(1, "one");
  hashTable.insert(2, "two");
  hashTable.insert(3, "three");
  BOOST_TEST(hashTable.size() == 3);
}

BOOST_AUTO_TEST_CASE(rehash)
{
  maslov::HashTable< int, std::string > hashTable(6);
  hashTable.insert(1, "one");
  hashTable.insert(2, "two");
  hashTable.rehash(10);
  BOOST_TEST(hashTable.size() == 2);
}

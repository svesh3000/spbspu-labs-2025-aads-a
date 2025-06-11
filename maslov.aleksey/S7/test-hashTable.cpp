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

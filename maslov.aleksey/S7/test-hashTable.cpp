#include <boost/test/unit_test.hpp>
#include <sstream>
#include "hashTable.hpp"

namespace maslov
{
  template< class Key, class T, class HS1, class HS2, class EQ >
  void printHashTable(std::ostream & out, const HashTable< Key, T, HS1, HS2, EQ > & hashTable)
  {
    if (hashTable.empty())
    {
      return;
    }
    auto it = hashTable.begin();
    out << it->first << ' ' << it->second;
    for (++it; it != hashTable.end(); ++it)
    {
      out << ' ' << it->first << ' ' << it->second;
    }
  }
}

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

BOOST_AUTO_TEST_CASE(find)
{
  maslov::HashTable< int, std::string > hashTable;
  bool check1 = hashTable.find(1) == hashTable.end();
  BOOST_TEST(check1);
  hashTable.insert(1, "one");
  hashTable.insert(2, "two");
  auto it1 = hashTable.find(1);
  BOOST_TEST(it1->first == 1);
  BOOST_TEST(it1->second == "one");
  auto it2 = hashTable.find(3);
  bool check2 = it2 == hashTable.end();
  BOOST_TEST(check2);
}

BOOST_AUTO_TEST_SUITE(elementAccess)

BOOST_AUTO_TEST_CASE(at)
{
  maslov::HashTable< int, std::string > hashTable;
  hashTable.insert(1, "one");
  hashTable.insert(2, "two");
  BOOST_TEST(hashTable.at(1) == "one");
  BOOST_TEST(hashTable.at(2) == "two");
}

BOOST_AUTO_TEST_CASE(operatorSquareBrackets)
{
  maslov::HashTable< int, std::string > hashTable;
  hashTable[1] = "one";
  hashTable[2] = "two";
  BOOST_TEST(hashTable[1] == "one");
  BOOST_TEST(hashTable[2] == "two");
  BOOST_TEST(hashTable.size() == 2);
}

BOOST_AUTO_TEST_SUITE_END()

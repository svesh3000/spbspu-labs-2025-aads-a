#include <boost/test/unit_test.hpp>
#include <boost/hash2/xxhash.hpp>
#include <string>
#include <iostream>
#include "hash-map.hpp"

using namespace savintsev;

BOOST_AUTO_TEST_CASE(hm_test_operator_sq)
{
  HashMap< int, std::string > book(10);

  book[1] = "apple";
  //std::cout << "1: " << book[1] << '\n';
  book[2] = "orange";
  //std::cout << "2: " << book[2] << '\n';
  book[3] = "banana";
  //std::cout << "3: " << book[3] << '\n';

  BOOST_TEST(book[1] == "apple");
  BOOST_TEST(book[2] == "orange");
  BOOST_TEST(book[3] == "banana");
}

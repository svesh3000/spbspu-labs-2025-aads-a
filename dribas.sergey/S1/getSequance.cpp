#include "getSequance.hpp"
#include <cstddef>
#include <iostream>
#include "list.hpp"
#include "constIterator.hpp"

dribas::List< std::pair< std::string, dribas::List< int > > > dribas::getSequance(std::istream& input) {
  List< std::pair< std::string, List< int > > > allSequance;
  std::string sequance;
  while (input >> sequance) {
    List< int > numbers;
    int number;
    while (input >> number) {
      numbers.push_back(number);
    }
    if (input.fail() && !input.eof()) {
      input.clear();
    }
    allSequance.push_back(std::make_pair(sequance, numbers));
  }
  return allSequance;
}
#include "getSequance.hpp"
#include <cstddef>
#include <iostream>
#include <limits>
#include "list.hpp"
#include "constIterator.hpp"

dribas::List< std::pair< std::string, dribas::List< int > > > dribas::getSequance(std::istream& input) {
  List< std::pair< std::string, List< int > > > allSequance;
  std::string sequance;
  while (input >> sequance) {
    List< int > numbers{};
    unsigned long long number = 0;
    while (input >> number) {
      if (number > static_cast< unsigned long long >(std::numeric_limits< int >::max())) {
        throw std::overflow_error("OverFlow!");
      }
      numbers.push_back(number);
    }
    allSequance.push_back(std::make_pair(sequance, numbers));
    input.clear();
  }
  return allSequance;
}

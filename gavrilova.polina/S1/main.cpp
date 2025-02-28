#include <forward_list>
#include <string>
#include "iostream"
#include "inputList.hpp"
#include "outputList.hpp"


int main() {
  using namespace gavrilova;
  std::forward_list< std::pair< std::string, std::forward_list< int > > > listOfPairs{};
  size_t numOfPairs = 0;
  size_t maxLen = 0;
  listOfPairs = inputList(std::cin, listOfPairs, maxLen, numOfPairs);
  listOfPairs.reverse();
  outNames(std::cout, listOfPairs);
  std::forward_list< int > sums {};
  try {
    sums = outNumbers(std::cout, listOfPairs, maxLen, numOfPairs);
  } catch(const std::overflow_error& e) {
    std::cerr << e.what();
    return 1;
  }
  outFwdListInt(std::cout, sums);
}


#include <forward_list>
#include <string>
#include "iostream"
#include "inputList.hpp"
#include "outputList.hpp"


int main() {
  using namespace gavrilova;
  std::forward_list< std::pair< std::string, std::forward_list< int > > > listOfPairs{};
  size_t numOfPairs = 0;
  std::string name;
  size_t maxLen = 0;
  size_t curLen = 0;
  while (std::cin >> name && !std::cin.eof()) {
    std::forward_list< int > numbers = inputNumbers(std::cin, curLen);
    maxLen = (maxLen < curLen) ? curLen : maxLen;
    if (curLen) {
      listOfPairs.push_front({name, numbers});
      ++numOfPairs;
    }
    if (numOfPairs == 4) {
      break;
    }
  }
  if (!numOfPairs) {
    std::cout << 0;
    return 0;
  }
  listOfPairs.reverse();
  outNames(std::cout, listOfPairs);
  std::forward_list< int > sums = outNumbers(std::cout, listOfPairs, maxLen, numOfPairs);
  outFwdListInt(std::cout, sums);
}


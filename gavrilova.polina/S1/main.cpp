#include <forward_list>
#include <string>
#include "iostream"
#include "inputList.hpp"
#include "outputList.hpp"


int main() {
  using namespace gavrilova;
  using ULL = unsigned long long;
  std::forward_list< std::pair< std::string, std::forward_list< ULL > > > listOfPairs{};
  size_t numOfPairs = 0;
  std::string name;
  size_t maxLen = 0;
  size_t curLen = 0;
  while (std::cin >> name && !std::cin.eof()) {
    std::forward_list< ULL > numbers = inputNumbers(std::cin, curLen);
    maxLen = (maxLen < curLen) ? curLen : maxLen;
    listOfPairs.push_front({name, numbers});
    ++numOfPairs;
    if (numOfPairs == 2) {
      break;
    }
  }
  listOfPairs.reverse();
  outNames(std::cout, listOfPairs);
  std::forward_list< ULL > sums {};
  try {
    sums = outNumbers(std::cout, listOfPairs, maxLen, numOfPairs);
  } catch(const std::overflow_error& e) {
    std::cout << "\n";
    std::cerr << e.what();
    return 1;
  }

  if (maxLen == 0) {
    std::cout << "0\n";
  } else {
    outFwdListULL(std::cout, sums);
  }
}


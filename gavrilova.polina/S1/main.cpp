#include <string>
#include <iostream>
#include "inputList.hpp"
#include "outputList.hpp"
#include "FwdList.hpp"

int main() {
  using namespace gavrilova;
  using ULL = unsigned long long;

  FwdList< std::pair< std::string, FwdList< ULL > > > listOfPairs{};
  // std::cout << "1\n";
  size_t numOfPairs = 0;
  std::string name;
  size_t maxLen = 0;
  auto cur_it = listOfPairs.begin();
  while (std::cin >> name && !std::cin.eof()) {
    // std::cout << "input_name\n";
    FwdList< ULL > numbers = inputNumbers(std::cin);
    // std::cout << "finish input numbers\n";
    maxLen = (maxLen < numbers.size()) ? numbers.size() : maxLen;
    std::pair< std::string, FwdList< ULL > > new_pair {name, numbers};
    listOfPairs.insert(cur_it, new_pair);
    // std::cout << "insert LOP\n";
    ++cur_it;
    ++numOfPairs;
  }
  // std::cout << "finnish input\n";

  if (numOfPairs) {
    outNames(std::cout, listOfPairs);
    std::cout << "\n";
  }
  // std::cout << "11\n";

  FwdList< ULL > sums {};
  try {
    sums = outNumbers(std::cout, listOfPairs, maxLen, numOfPairs);
  } catch(const std::overflow_error& e) {
    std::cout << "\n";
    std::cerr << e.what();
    return 1;
  }
  if (maxLen == 0) {
    std::cout << "0" << "\n";
  } else {
    outFwdListULL(std::cout, sums);
  }
  // std::cout << "1\n";
}

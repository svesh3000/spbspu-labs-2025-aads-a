#include <iostream>
#include <string>
#include "FwdList.hpp"
#include "inputList.hpp"
#include "outputList.hpp"

int main()
{
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
<<<<<<< HEAD
    std::pair< std::string, FwdList< ULL > > new_pair {name, numbers};
    listOfPairs.insert(cur_it, new_pair);
    // std::cout << "insert LOP\n";
=======
    std::pair< std::string, FwdList< ULL > > new_pair{name, numbers};
    listOfPairs.insert(cur_it, new_pair);
>>>>>>> gavrilova.polina/S2
    ++cur_it;
    ++numOfPairs;
  }
  // std::cout << "finnish input\n";

  if (numOfPairs) {
    outNames(std::cout, listOfPairs);
    std::cout << "\n";
  }
  // std::cout << "11\n";

  if (maxLen == 0) {
    std::cout << "0" << "\n";
    return 0;
  }

  FwdList< ULL > sums{};
  try {
    sums = outNumbers(std::cout, listOfPairs, maxLen, numOfPairs);
    std::cout << "\n";
  } catch (const std::overflow_error& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
<<<<<<< HEAD
  if (maxLen == 0) {
    std::cout << "0" << "\n";
  } else {
    outFwdListULL(std::cout, sums);
  }
 std::cout << "1\n";
=======

  outFwdListULL(std::cout, sums);
  std::cout << "\n";
>>>>>>> gavrilova.polina/S2
}

#include <iostream>
#include <utility>
#include <list>
#include <limits>
#include <iomanip>
#include "list_manipulations.hpp"
#include "forward_list.hpp"

int main()
{
  std::list < std::pair<std::string, std::list<unsigned long long>>> myList;
  std::string sequenceName = "";
  while (std::cin >> sequenceName)
  {
    unsigned long long element = 0;
    std::list<unsigned long long> temporaryList{};
    while (std::cin >> element)
    {
      temporaryList.push_back(element);
    }
    std::pair<std::string, std::list<unsigned long long>> temporaryPair{ sequenceName, temporaryList };
    myList.push_back(temporaryPair);
    if (std::cin.eof())
    {
      break;
    }
    std::cin.clear();
  }
  lanovenko::printSequencesName(myList, std::cout);
  size_t maxSize = 0;
  for (auto it : myList)
  {
    if (maxSize < it.second.size())
    {
      maxSize = it.second.size();
    }
  }
  bool sumLimit = false;
  lanovenko::printSequences(myList, maxSize, sumLimit, std::cout);
  if (sumLimit)
  {
    std::cerr << "Sum limit!\n";
    return 1;
  }
}

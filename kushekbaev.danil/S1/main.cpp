#include <iostream>
#include <limits>
#include "utilityFunctions.hpp"

using pairedList = std::list< std::pair<std::string, std::list< unsigned long long > > >;

int main()
{
  pairedList pairsList;
  std::string listNumber = "";

  while (std::cin >> listNumber)
  {
    std::list< unsigned long long > valueList;
    unsigned long long value = 0;
    while (std::cin >> value)
    {
      valueList.push_back(value);
    }
    pairsList.push_back(std::make_pair(listNumber, valueList));
    std::cin.clear();
  }

  if (pairsList.size() == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  std::cout << pairsList.begin()->first;
  for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";

  size_t maxSize = kushekbaev::calcOfSize(pairsList);
  std::list< unsigned long long > sumList;

  for (size_t i = 0; i != maxSize; ++i)
  {
    std::list< unsigned long long > rowList;
    for (auto j = pairsList.begin(); j != pairsList.end(); ++j)
    {
      if (!j->second.empty())
      {
        rowList.push_back(j->second.front());
        j->second.pop_front();
      }
    }
    if (!rowList.empty())
    {
      std::cout << *sumList.begin();
      for (auto j = ++sumList.begin(); j != sumList.end(); ++j)
      {
        std::cout << "_" << *j;
      }
    }
  }
}

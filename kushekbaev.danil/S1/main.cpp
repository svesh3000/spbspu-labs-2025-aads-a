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

  if (pairsList.empty())
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

  try
  {
  for (size_t i = 0; i != maxSize; ++i)
    {
      std::list< unsigned long long > rowList;
      for (auto tmp_it = pairsList.begin(); tmp_it != pairsList.end(); ++tmp_it)
      {
        if (!tmp_it->second.empty())
        {
          rowList.push_back(tmp_it->second.front());
          tmp_it->second.pop_front();
        }
      }
      if (!rowList.empty())
      {
        std::cout << *sumList.begin();
        for (auto tmp_it = ++sumList.begin(); tmp_it != sumList.end(); ++tmp_it)
        {
          std::cout << " " << *tmp_it;
        }
        std::cout << "\n";
        sumList.push_back(kushekbaev::calcSumOfList(rowList));
      }
    }
  }
  catch (const std::overflow_error&)
  {
    std::cerr << "Overflow!\n";
    return 1;
  }

  std::cout << *sumList.begin();
  for (auto it = ++sumList.begin(); it != sumList.end(); ++it)
  {
    std::cout << " " << *it;
  }
}

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

  for (size_t i = 0; i < maxSize; ++i)
  {
    std::list< unsigned long long > outputList = pairsList.begin()->second;
    while (!outputList.empty())
    {
      std::cout << outputList.front();
      if (!(outputList.size() == 1))
      {
        std::cout << "_";
      }
      outputList.pop_front();
    }
    std::cout << "\n";
  }

  unsigned long long sum = 0;

  try
  {
    sum = kushekbaev::calcOfSum(pairsList);
  }
  catch (const std::overflow_error&)
  {
    std::cerr << "Overflow!\n";
    return 1;
  }

  auto valueList = pairsList.begin()->second;

  for (auto it = ++valueList.begin(); it != valueList.end(); ++it)
  {
    std::cout << "_" << *it;
  }
  std::cout << sum << "\n";
}

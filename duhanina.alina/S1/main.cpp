#include <iostream>
#include <utility>
#include <string>
#include <algorithm>
#include "list.hpp"


namespace
{
  using pair = duhanina::List< std::pair< std::string, duhanina::List< unsigned long long > > >;

  void printNames(const pair& ListPair)
  {
    for (auto it = ListPair.begin(); it != ListPair.end(); ++it)
    {
      std::cout << it->first << " ";
    }
    std::cout << "\n";
  }

  duhanina::List< duhanina::List< unsigned long long > > generateListPair(pair& ListPair)
  {
    duhanina::List< duhanina::List< unsigned long long > > resultListPair;
    bool allListsEmpty = false;
    while (!allListsEmpty)
    {
      allListsEmpty = true;
      duhanina::List< unsigned long long > currentSequence;
      for (auto it = ListPair.begin(); it != ListPair.end(); ++it)
      {
        if (!it->second.empty()) {
          currentSequence.push_back(it->second.front());
          it->second.pop_front();
          allListsEmpty = false;
        }
      }
      if (!currentSequence.empty())
      {
        resultListPair.push_back(currentSequence);
      }
    }
    return resultListPair;
  }

  void printListPair(const duhanina::List< duhanina::List< unsigned long long > >& ListPair)
  {
    for (auto it = ListPair.begin(); it != ListPair.end(); ++it)
    {
      for (auto numIt = it->begin(); numIt != it->end(); ++numIt)
      {
        std::cout << *numIt;
      }
      std::cout << "\n";
    }
  }

  void printSums(const duhanina::List< duhanina::List< unsigned long long > >& ListPair)
  {
    duhanina::List< unsigned long long > sums;
    for (auto it = ListPair.begin(); it != ListPair.end(); ++it)
    {
      unsigned long long sum = 0;
      for (auto numIt = it->begin(); numIt != it->end(); ++numIt)
      {
        if (sum > std::numeric_limits< unsigned long long >::max() - *numIt)
        {
          throw;
        }
        sum += *numIt;
      }
      sums.push_back(sum);
    }
    for (auto it = sums.begin(); it != sums.end(); ++it)
    {
      std::cout << *it << " ";
    }
    std::cout << "\n";
  }
}

int main()
{
  duhanina::List< std::pair< std::string, duhanina::List< unsigned long long > > > ListPair;
  std::string name;
  while (std::cin >> name)
  {
    duhanina::List< unsigned long long > numbersList;
    unsigned long long number = 0;
    while (std::cin >> number)
    {
      numbersList.push_back(number);
    }
    ListPair.push_back(std::make_pair(name, numbersList));
    std::cin.clear();
  }
  if (ListPair.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  printNames(ListPair);
  auto resultListPair = generateListPair(ListPair);
  printListPair(resultListPair);
  try
  {
    printSums(resultListPair);
  }
  catch (const std::exception&)
  {
    std::cerr << "Error\n";
    return 1;
  }
  return 0;
}

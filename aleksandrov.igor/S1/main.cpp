#include <iostream>
#include <string>
#include <utility>
#include <forward_list>
#include "sum.hpp"

namespace aleksandrov
{
  void outputIntList(const std::forward_list< int >& intList, std::ostream& output)
  {
    for (auto it = intList.begin(); it != intList.end(); ++it)
    {
      std::cout << *it;
      if (it != intList.end())
      {
        output << " ";
      }
    }
  }
}

int main()
{
  std::forward_list< std::pair< std::string, std::forward_list < int > > > list;
  std::string listName;
  size_t maxSubListSize = 0;

  auto listIter = list.before_begin();
  while (std::cin >> listName)
  {
    std::forward_list< int > numList;
    auto numListIter = numList.before_begin();
    int num = 0;
    size_t numCount = 0;
    while (std::cin >> num)
    {
      numList.insert_after(numListIter, num);
      ++numListIter;
      ++numCount;
      if (maxSubListSize < numCount)
      {
        maxSubListSize = numCount;
      }
    }
    std::cin.clear();
    list.insert_after(listIter, std::make_pair(listName, numList));
    ++listIter;
  }

  std::forward_list< std::string > nameList;
  auto nameListIter = nameList.before_begin();
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    nameList.insert_after(nameListIter, it->first);
    ++nameListIter;
  }

  if (!nameList.empty())
  {
    std::cout << nameList.front();
  }
  for (auto it = ++nameList.begin(); it != nameList.end(); ++it)
  {
    std::cout << " " << *it;
  }
  std::cout << "\n";

  std::forward_list< std::forward_list < int > > yaNumList;
  auto yaNumListIter = yaNumList.before_begin();
  size_t shift = 0;
  while (shift != maxSubListSize)
  {
    std::forward_list< int > numList;
    auto numListIter = numList.before_begin();
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      auto shiftedIt = it->second.begin();
      for (size_t i = 0; i < shift && shiftedIt != it->second.end(); ++i)
      {
        ++shiftedIt;
      }
      if (shiftedIt != it->second.end())
      {
        numList.insert_after(numListIter, *shiftedIt);
        ++numListIter;
      }
    }
    ++shift;
    yaNumList.insert_after(yaNumListIter, numList);
    ++yaNumListIter;
  }

  for (auto it = yaNumList.begin(); it != yaNumList.end(); ++it)
  {
    aleksandrov::outputIntList(*it, std::cout);
    std::cout << "\n";
  }

  std::forward_list< int > sumList;
  auto sumListIter = sumList.before_begin();
  for (auto it = yaNumList.begin(); it != yaNumList.end(); ++it)
  {
    try
    {
      int sum = aleksandrov::calcIntSum(*it);
      sumList.insert_after(sumListIter, sum);
      ++sumListIter;
    }
    catch (const std::overflow_error& e)
    {
      std::cerr << e.what();
      break;
    }
  }
  aleksandrov::outputIntList(sumList, std::cout);
  std::cout << "\n";
}


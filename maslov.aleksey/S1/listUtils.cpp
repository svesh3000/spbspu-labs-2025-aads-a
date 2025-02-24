#include "listUtils.hpp"
#include <iostream>

void maslov::print(std::ostream & out, const list & listOfPairs, size_t maxSize)
{
  out << listOfPairs.begin()->first;
  for (auto it = ++listOfPairs.begin(); it != listOfPairs.end(); ++it)
  {
    out << " " << it->first;
  }
  out << "\n";
  std::forward_list< int > sums;
  auto itSum = sums.before_begin();
  for (size_t i = 0; i < maxSize; ++i)
  {
    int sum = 0;
    bool flagPrint = false;
    for (auto it = listOfPairs.begin(); it != listOfPairs.end(); ++it)
    {
      if (!it->second.empty())
      {
        bool flagEnd = true;
        auto itNum = it->second.begin();
        for (size_t j = 0; j < i; ++j)
        {
          itNum++;
          if (itNum == it->second.end())
          {
            flagEnd = false;
            break;
          }
        }
        if (flagEnd)
        {
          if (flagPrint)
          {
            out << " ";
          }
          sum += *itNum;
          out << *itNum;
          flagPrint = true;
        }
      }
    }
    itSum = sums.insert_after(itSum, sum);
    out << "\n";
  }
  auto it = sums.begin();
  out << *it;
  for (++it; it != sums.end(); ++it)
  {
    out << " " << *it;
  }
}

#include "utilityFunctions.hpp"

using pairedList = std::list< std::pair< std::string, std::list< unsigned long long > > >;

namespace kushekbaev
{
  size_t calcOfSize(pairedList pairsList)
  {
    size_t maxSize = 0;

    for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
    {
      maxSize = std::max(maxSize, it->second.size());
    }

    return maxSize;
  }

  std::list< unsigned long long > deletingSpaces(pairedList pairsList, std::list< unsigned long long > valueList)
  {
    for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
    {
      if (!it->second.empty())
      {
        valueList.push_back(it->second.front());
      }
    }
    return valueList;
  }

  unsigned long long calcOfSum(pairedList pairsList)
  {
    unsigned long long sum = 0;
    auto valueList = pairsList.begin()->second;

    for (auto it = ++valueList.begin(); it != valueList.end(); ++it)
    {
      if (sum > std::numeric_limits< unsigned long long >::max() - *it)
      {
        throw std::overflow_error("Overflow!");
      }

      sum += *it;
    }

    return sum;
  }
}

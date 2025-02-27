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
        it->second.pop_front();
      }
    }
    return valueList;
  }

  unsigned long long calcOfSum(std::list< unsigned long long > valueList)
  {
    unsigned long long sum = 0;

    for (auto it = ++valueList.begin(); it != valueList.end(); ++it)
    {
      if (sum > std::numeric_limits< unsigned long long >::max() - *it)
      {
        throw std::logic_error("Overflow!");
        return 1;
      }

      sum += *it;
    }

    return sum;
  }
}

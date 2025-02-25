#include "sum.hpp"
#include <forward_list>
#include <limits>
#include <stdexcept>

namespace aleksandrov
{
  unsigned long long calcSum(const std::forward_list< unsigned long long >& list)
  {
    const unsigned long long maxValue = std::numeric_limits< unsigned long long >::max();
    unsigned long long sum = 0;

    for (auto it = list.begin(); it != list.end(); ++it)
    {
      unsigned long long value = *it;
      if (maxValue - sum > value)
      {
        sum += value;
      }
      else
      {
        throw std::overflow_error("There was an overflow error!");
      }
    }
    return sum;
  }
}


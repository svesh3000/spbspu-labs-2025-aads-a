#include "sum.hpp"
#include <forward_list>
#include <limits>
#include <stdexcept>

namespace aleksandrov
{
  int sign(int num)
  {
    return (num > 0) ? 1 : ((num < 0) ? -1 : 0);
  }

  bool sameSign(int a, int b)
  {
    return sign(a) * sign(b) > 0;
  }

  int calcIntSum(const std::forward_list< int >& intList)
  {
    const int maxInt = std::numeric_limits< int >::max();
    const int minInt = std::numeric_limits< int >::min();
    int sum = 0;
    for (auto it = intList.begin(); it != intList.end(); ++it)
    {
      int el = *it;
      if (sameSign(sum, el) && (sum > 0))
      {
        if (maxInt - sum > el)
        {
          sum += el;
        }
        else
        {
          throw std::overflow_error("Overflow error!");
        }
      }
      else if (sameSign(sum, el) && (sum < 0))
      {
        if (minInt - sum < el)
        {
          sum += el;
        }
        else
        {
          throw std::overflow_error("Overflow error!");
        }
      }
      else if (!sameSign(sum, el))
      {
        sum += el;
      }
    }
    return sum;
  }
}


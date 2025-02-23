#ifndef SUM_HPP
#define SUM_HPP

#include <forward_list>

namespace aleksandrov
{
  int sign(int num);
  bool sameSign(int a, int b);
  int calcIntSum(const std::forward_list< int >& intList);
}

#endif


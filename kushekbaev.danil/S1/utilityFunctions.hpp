#ifndef UTILITYFUNCTIONS_HPP
#define UTILITYFUNCTIONS_HPP

#include <cstddef>
#include <list>
#include <string>
#include <limits>
#include <stdexcept>

using pairedList = std::list< std::pair< std::string, std::list< unsigned long long > > >;

namespace kushekbaev
{
  size_t calcOfSize(pairedList pairsList);
  std::list< unsigned long long > deletingSpaces(pairedList pairsList, std::list< unsigned long long > valueList);
  unsigned long long calcSumOfList(std::list< unsigned long long >& list);
}

#endif

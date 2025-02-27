#ifndef UTILITYFUNCTIONS_HPP
#define UTILITYFUNCTIONS_HPP

#include <cstddef>
#include <list>
#include <string>
#include <limits>
#include <stdexcept>

namespace kushekbaev
{
  size_t calcOfSize(pairedList pairsList);
  std::list< unsigned long long > deletingSpaces(pairedList pairsList, std::list< unsigned long long > valueList);
  unsigned long long calcOfSum(std::list< unsigned long long > valueList, std::ostream& out);
}

#endif

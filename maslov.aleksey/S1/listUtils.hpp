#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

#include <iosfwd>
#include <forward_list>
#include <string>
#include "list.hpp"

using list = maslov::FwdList< std::pair< std::string, maslov::FwdList< size_t > > >;

namespace maslov
{
  void printData(std::ostream & out, list & listOfPairs, size_t maxSize);
}
#endif

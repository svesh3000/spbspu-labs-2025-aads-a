#ifndef LIST_UTILS_HPP
#define LIST_UTILS_HPP

#include <iosfwd>
#include <forward_list>
#include <string>
#include "list.hpp"

using list = std::forward_list< std::pair< std::string, std::forward_list< int > > >;

namespace maslov
{
  void print(std::ostream & out, const list & listOfPairs, size_t maxSize);
}
#endif
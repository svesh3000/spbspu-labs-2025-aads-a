#ifndef DICT_UTILS_HPP
#define DICT_UTILS_HPP
#include <iostream>
#include <list/list.hpp>

namespace alymova
{
  std::istream& operator>>(std::istream& in, List< std::string >& list);
  std::ostream& operator<<(std::ostream& out, const List< std::string >& list);
}
#endif

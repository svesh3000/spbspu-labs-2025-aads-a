#ifndef WORKFLOWS_HPP
#define WORKFLOWS_HPP
#include <iostream>
#include "list.hpp"
#include <ostream>

using numberList = kiselev::List< unsigned long long >;
using pair = std::pair< std::string, numberList >;
using list = kiselev::List< pair >;

namespace kiselev
{
  std::istream& createList(std::istream& input, list& list_);
  std::ostream& output(std::ostream& output, list& list_);
}
#endif

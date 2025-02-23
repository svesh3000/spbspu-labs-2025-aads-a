#ifndef WORKFLOWS_HPP
#define WORKFLOWS_HPP
#include <iostream>
#include <ostream>
#include "list.hpp"

using numberList = kiselev::List< unsigned long long >;
using pair = std::pair< std::string, numberList >;
using list = kiselev::List< pair >;

namespace kiselev
{
  list createList(std::istream& input);
  std::ostream& output(std::ostream& output, list& list_);
}
#endif

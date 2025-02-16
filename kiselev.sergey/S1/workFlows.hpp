#ifndef WORKFLOWS_HPP
#define WORKFLOWS_HPP
#include <iostream>
#include <list>
#include <ostream>

using numberList = std::list< unsigned long long >;
using pair = std::pair< std::string, numberList >;
using list = std::list< pair >;

namespace kiselev
{
  std::istream& createList(std::istream& input, list& list_);
  std::ostream& output(std::ostream& output, list& list_);
}
#endif

#ifndef ACTIONS_HPP
#define ACTIONS_HPP
#include <iostream>
#include <ostream>
#include "list.hpp"

namespace bocharov
{
  using numberList = List< unsigned long long >;
  using pair = std::pair< std::string, numberList >;
  using list = List< pair >;
  list createList(std::istream & input);
  std::ostream & output(std::ostream & output, list & list_);
}
#endif

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>
#include "tree.hpp"
#include <map>

namespace kiselev
{
  using data = std::map< size_t, std::string >;
  using dataset = std::map< std::string, data >;
  void print(std::ostream&, std::istream&, const dataset&);
  void complement(std::istream&, dataset&);
  void intersect(std::istream&, dataset&);
  void unite(std::istream&, dataset&);
}
#endif

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>
#include "tree.hpp"

namespace brevnov
{
  using data = AVLTrees< size_t, std::string >;
  using dataset = AVLTrees< std::string, data >;
  void print(std::ostream&, std::istream&, const dataset&);
  void complement(std::istream&, dataset&);
  void intersect(std::istream&, dataset&);
  void unite(std::istream&, dataset&);
}
#endif

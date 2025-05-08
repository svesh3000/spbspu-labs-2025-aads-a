#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <tree/tree.hpp>
#include "graph.hpp"

namespace demehin
{
  using MapOfGraphs = demehin::Tree< std::string, Graph >;

  void printGraphsNames(std::ostream&, const MapOfGraphs);
  void printVertexesNames(std::ostream&, std::istream&, const MapOfGraphs);
}

#endif

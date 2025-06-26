#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP
#include <fstream>
#include "graph_collection.hpp"

namespace abramov
{
  std::ifstream &readGraphs(std::ifstream &in, GraphCollection &collect);
  void printVertSorted(const GraphCollection &collect, const std::string &name, std::ostream &out);
}
#endif

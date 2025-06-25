#ifndef GRAPH_UTILS_HPP
#define GRAPH_UTILS_HPP
#include <fstream>
#include "graph_collection.hpp"

namespace abramov
{
  std::ifstream &readGraphs(std::ifstream &in, GraphCollection &collect);
}
#endif

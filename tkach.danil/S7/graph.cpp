#include "graph.hpp"

namespace tkach
{
  void Graph::addEdge(const std::string& vert1, const std::string& vert2, size_t weight)
  {
    edges_.insert({std::make_pair(vert1, vert2), weight});
  }
}
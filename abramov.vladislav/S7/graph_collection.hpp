#ifndef GRAPH_COLLECTION_HPP
#define GRAPH_COLLECTION_HPP
#include <ostream>
#include <algorithm>
#include "graph.hpp"

namespace abramov
{
  struct GraphCollection
  {
    GraphCollection();
    void addGraph(const Graph &graph);
    SimpleArray< std::string > getAllGraphsSorted() const;
    void printAllGraphs(std::ostream &out) const;
  private:
    HashTable< std::string, Graph > graphs;

  };
}
#endif

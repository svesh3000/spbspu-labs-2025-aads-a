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

abramov::GraphCollection::GraphCollection():
  graphs(HashTable< std::string, Graph >{})
{}

void abramov::GraphCollection::addGraph(const Graph &graph)
{
  graphs.insert(graph.getName(), graph);
}

abramov::SimpleArray< std::string > abramov::GraphCollection::getAllGraphsSorted() const
{
  SimpleArray< std::string > names;
  for (auto it = graphs.cbegin(); it != graphs.cend(); ++it)
  {
    names.pushBack(it->first);
  }
  if (names.size() > 0)
  {
    std::sort(&names[0], &names[0] + names.size());
  }
  return names;
}

void abramov::GraphCollection::printAllGraphs(std::ostream &out) const
{
  auto names = getAllGraphsSorted();
  for (size_t i = 0; i < names.size(); ++i)
  {
    out << names[i] << "\n";
  }
}
#endif

#include "graph_collection.hpp"

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


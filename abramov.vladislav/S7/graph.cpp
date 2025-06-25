#include "graph.hpp"

abramov::Graph::Graph(const std::string &n):
  adj_list(HashTable< std::string, SimpleArray< Edge > >{}),
  name(n),
  edge_count(0)
{}

void abramov::Graph::addEdge(const std::string &from, const std::string &to, size_t w)
{
  Edge edge(from, to, w);
  auto it = adj_list.find(from);
  if (it != adj_list.end())
  {
    it->second.pushBack(edge);
  }
  else
  {
    SimpleArray< Edge > edges;
    edges.pushBack(edge);
    adj_list.insert(from, edges);
  }
  ++edge_count;
}

const std::string &abramov::Graph::getName() const noexcept
{
  return name;
}

size_t abramov::Graph::getEdgeCount() const noexcept
{
  return edge_count;
}

size_t abramov::Graph::getVertexCount() const noexcept
{
  return adj_list.size();
}

const abramov::SimpleArray< abramov::Edge > *abramov::Graph::getEdges(const std::string &vert) const
{
  auto it = adj_list.cfind(vert);
  if (it != adj_list.cend())
  {
    return &(it->second);
  }
  return nullptr;
}

bool abramov::Graph::hasVertex(const std::string &vert) const
{
  return adj_list.cfind(vert) != adj_list.cend();
}

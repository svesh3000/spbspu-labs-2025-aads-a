#include "graph.hpp"

abramov::Graph::Graph(const std::string &n):
  adj_list(HashTable< std::string, SimpleArray< Edge > >{}),
  name(n),
  edge_count(0)
{}

abramov::Graph::Graph(const Graph &other):
  adj_list(other.adj_list),
  name(other.name),
  edge_count(other.edge_count)
{}

void abramov::Graph::swap(Graph &other) noexcept
{
  std::swap(adj_list, other.adj_list);
  std::swap(name, other.name);
  std::swap(edge_count, other.edge_count);
}

abramov::Graph &abramov::Graph::operator=(const Graph &other)
{
  Graph temp(other);
  swap(temp);
  return *this;
}

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

typename abramov::Graph::Iterator abramov::Graph::begin()
{
  return adj_list.begin();
}

typename abramov::Graph::Iterator abramov::Graph::end()
{
  return adj_list.end();
}

typename abramov::Graph::ConstIterator abramov::Graph::cbegin() const
{
  return adj_list.cbegin();
}

typename abramov::Graph::ConstIterator abramov::Graph::cend() const
{
  return adj_list.cend();
}

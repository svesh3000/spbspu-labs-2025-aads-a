#include "graph.hpp"

void alymova::Graph::addEdge(std::string vertex1, std::string vertex2, size_t weight)
{
  edges.insert(std::make_pair(std::make_pair(vertex1, vertex2), weight));
  addVertex(vertex1);
  addVertex(vertex2);
}

void alymova::Graph::cutEdge(std::string vertex1, std::string vertex2, size_t weight)
{
  std::pair< std::string, std::string > vertex_pair(vertex1, vertex2);
  for (auto it = edges.begin(); it != edges.end(); it++)
  {
    if (it->first == vertex_pair && it->second == weight)
    {
      edges.erase(it);
      return;
    }
  }
  throw std::logic_error("<INVALID COMMAND>");
}

void alymova::Graph::addVertex(std::string vertex)
{
  if (!hasVertex(vertex))
  {
    vertexes.push_back(vertex);
  }
}

bool alymova::Graph::hasVertex(std::string vertex) const
{
  for (auto it = vertexes.begin(); it != vertexes.end(); it++)
  {
    if (*it == vertex)
    {
      return true;
    }
  }
  return false;
  //return vertexes.find(vertex) != vertexes.end();
}

void alymova::Graph::merge(const Graph& other)
{
  for (auto it = other.edges.begin(); it != other.edges.end(); it++)
  {
    addEdge(it->first.first, it->first.second, it->second);
  }
}

alymova::BoundMap alymova::Graph::getOutbound(std::string vertex) const
{
  BoundMap outbound;
  for (auto it = edges.begin(); it != edges.end(); it++)
  {
    if (it->first.first == vertex)
    {
      outbound[it->first.second].push_back(it->second);
    }
  }
  return outbound;
}

alymova::BoundMap alymova::Graph::getInbound(std::string vertex) const
{
  BoundMap inbound;
  for (auto it = edges.begin(); it != edges.end(); it++)
  {
    if (it->first.second == vertex)
    {
      inbound[it->first.first].push_back(it->second);
    }
  }
  return inbound;
}

std::istream& alymova::operator>>(std::istream& in, Graph& graph)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t cnt_edges;
  in >> cnt_edges;

  std::string vertex1, vertex2;
  size_t weidth;
  for (size_t i = 0; i < cnt_edges; i++)
  {
    if (!(in >> vertex1 >> vertex2 >> weidth))
    {
      throw std::logic_error("<INCORRECT GRAPH DESCRIPTION>");
    }
    graph.addEdge(vertex1, vertex2, weidth);
  }
  return in;
}
std::ostream& alymova::operator<<(std::ostream& out, const Graph& graph)
{
  std::ostream::sentry s(out);
  if (!s)
  {
    return out;
  }
  auto it = graph.edges.begin();
  if (it != graph.edges.end())
  {
    out << it->first.first << ' ' << it->first.second << ' ' << it->second;
    it++;
  }
  for (; it != graph.edges.end(); it++)
  {
    out << '\n' << it->first.first << ' ' << it->first.second << ' ' << it->second;
  }
  return out;
}

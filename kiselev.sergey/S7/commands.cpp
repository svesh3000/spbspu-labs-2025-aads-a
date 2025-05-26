#include "commands.hpp"
#include <map>
#include <stdexcept>
#include <string>

namespace
{
  void bound(std::ostream& out, std::istream& in, const kiselev::Graphs& graphs, const std::string& b)
  {
    std::string graph;
    std::string vertex;
    in >> graph >> vertex;
    auto graphIt = graphs.find(graph);
    if (graphIt == graphs.end())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    std::map< std::string, std::string > vertexes = graphIt->second.getVertexes();
    if (vertexes.find(vertex) == vertexes.end())
    {
      throw std::logic_error("<INVALID COMMAND>")
    }
    std::map< std::string, std::map< unsigned int, unsigned int > > bound;
    if (b == "out")
    {
      bound = graphIt->second.getOutBound(vertex);
    }
    else
    {
      bound = graphIt->second.getInBound(vertex);
    }
    for (auto it = bound.begin(); it != bound.end(); ++it)
    {
      out << it->first;
      for (auto weightIt = it->second.begin(); weightIt != it->second.end(); ++weightIt)
      {
        out << " " << weightIt->first;
      }
      out << "\n";
    }
  }
}
void kiselev::graphs(std::ostream& out, const Graphs& graphs)
{
  for (auto it = graphs.begin(); it != graphs.end(); ++it)
  {
    out << it->first << "\n";
  }
}

void kiselev::vertexes(std::ostream& out, std::istream& in, const Graphs& graphs)
{
  std::string graph;
  in >> graph;
  auto it = graphs.find(graph);
  if (it == graphs.end())
  {
    std::logic_error("<INVALID COMMAND>");
  }
  std::map< std::string, std::string > vertexes = it->second.getVertexes();
  for (auto iter = vertexes.begin(); iter != vertexes.end(); ++iter)
  {
    out << iter->first << "\n";
  }
}

void kiselev::outBound(std::ostream& out, std::istream& in, const Graphs& graphs)
{
  bound(out, in, graphs, "out");
}

void kiselev::inBound(std::ostream& out, std::istream& in, const Graphs& graphs)
{
  bound(out, in, graphs, "in");
}

void kiselev::bind(std::istream& in, Graphs& graphs)
{
  std::string graph;
  std::string v1;
  std::string v2;
  unsigned int weight;
  in >> graph >> v1 >> v2 >> weight;
  auto it = graphs.find(graph);
  if (it == graphs.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  it->second.addEdge(v1, v2, weight);
}

void kiselev::cut(std::istream& in, Graphs& graphs)
{
  std::string graph;
  std::string v1;
  std::string v2;
  unsigned int weight;
  in >> graph >> v1 >> v2 >> weight;
  auto graphIt = graphs.find(graph);
  if (graphIt == graphs.end() || !graphIt->second.removeEdge(v1, v2, weight))
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

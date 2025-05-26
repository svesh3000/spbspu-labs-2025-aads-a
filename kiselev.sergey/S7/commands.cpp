#include "commands.hpp"
#include <map>
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
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::map< std::string, std::string > vertexes = graphIt->second.getVertexes();
    if (vertexes.find(vertex) == vertexes.end())
    {
      out << "<INVALID COMMAND>\n";
      return;
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
    out << "<INVALID COMMAND>\n";
    return;
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

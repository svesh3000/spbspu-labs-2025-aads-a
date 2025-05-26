#include "commands.hpp"
#include <map>
#include <string>

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

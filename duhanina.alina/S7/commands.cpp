#include "commands.hpp"
#include <string>

void duhanina::inputGraphs(std::istream& in, MapOfGraphs& graphs)
{
  std::string name;
  size_t edgeCount;
  while (in >> name >> edgeCount)
  {
    Graph currentGraph;
    for (size_t i = 0; i < edgeCount; ++i)
    {
      std::string from;
      std::string to;
      unsigned int weight;
      if (!(in >> from >> to >> weight))
      {
        throw std::runtime_error("Invalid input format");
      }
      currentGraph.addEdge(from, to, weight);
    }
    graphs[name] = currentGraph;
  }
}

void duhanina::printGraphsNames(std::ostream& out, const MapOfGraphs& graphs)
{
  for (auto it = graphs.begin(); it != graphs.end(); ++it)
  {
    out << it->first << "\n";
  }
}

void duhanina::printVertexesNames(std::ostream& out, std::istream& in, const MapOfGraphs& graphs)
{
  std::string graphName;
  in >> graphName;
  auto it = graphs.find(graphName);
  if (it == graphs.cend())
  {
    throw std::invalid_argument("Invalid command");
  }
  List< Graph::Vertex > vertices = it->second.getVertices();
  for (auto vit = vertices.begin(); vit != vertices.end(); ++vit)
  {
    out << *vit << "\n";
  }
}

void duhanina::printOutbounds(std::ostream& out, std::istream& in, const MapOfGraphs& graphs)
{
  std::string graphName;
  std::string vertex;
  in >> graphName >> vertex;
  auto it = graphs.find(graphName);
  if (it == graphs.cend() || !it->second.hasVertex(vertex))
  {
    throw std::invalid_argument("Invalid command");
  }
  Tree< Graph::Vertex, Graph::WeightsList, std::less< std::string > > outbound = it->second.getOutbound(vertex);
  if (outbound.size() == 0)
  {
    out << "\n";
    return;
  }
  for (auto oit = outbound.begin(); oit != outbound.end(); ++oit)
  {
    out << oit->first;
    for (auto wit = oit->second.begin(); wit != oit->second.end(); ++wit)
    {
      out << " " << *wit;
    }
    out << "\n";
  }
}

void duhanina::printInbounds(std::ostream& out, std::istream& in, const MapOfGraphs& graphs)
{
  std::string graphName;
  std::string vertex;
  in >> graphName >> vertex;
  auto it = graphs.find(graphName);
  if (it == graphs.cend() || !it->second.hasVertex(vertex))
  {
    throw std::invalid_argument("Invalid command");
  }
  Tree< Graph::Vertex, Graph::WeightsList, std::less< std::string > > inbound = it->second.getInbound(vertex);
  if (inbound.size() == 0)
  {
    out << "\n";
    return;
  }
  for (auto iit = inbound.begin(); iit != inbound.end(); ++iit)
  {
    out << iit->first;
    for (auto wit = iit->second.begin(); wit != iit->second.end(); ++wit)
    {
      out << " " << *wit;
    }
    out << "\n";
  }
}

void duhanina::bind(std::istream& in, MapOfGraphs& graphs)
{
  std::string graphName;
  std::string from;
  std::string to;
  Graph::Weight weight;
  in >> graphName >> from >> to >> weight;
  auto it = graphs.find(graphName);
  if (it == graphs.end())
  {
    throw std::invalid_argument("Invalid command");
  }
  it->second.addEdge(from, to, weight);
}

void duhanina::cut(std::istream& in, MapOfGraphs& graphs)
{
  std::string graphName;
  std::string from;
  std::string to;
  Graph::Weight weight;
  in >> graphName >> from >> to >> weight;
  auto it = graphs.find(graphName);
  if (it == graphs.end() || !it->second.hasEdge(from, to, weight))
  {
    throw std::invalid_argument("Invalid command");
  }
  it->second.removeEdge(from, to, weight);
}

void duhanina::create(std::istream& in, MapOfGraphs& graphs)
{
  std::string graphName;
  in >> graphName;
  if (graphs.find(graphName) != graphs.end())
  {
    throw std::invalid_argument("Invalid command");
  }
  graphs.insert(std::make_pair(graphName, Graph()));
}
/*
void duhanina::merge(std::istream& in, MapOfGraphs& graphs)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  if (graphs.find(newName) != graphs.end() || graphs.find(name1) == graphs.end() || graphs.find(name2) == graphs.end())
  {
    throw std::invalid_argument("Invalid command");
  }
  const Graph& g1 = graphs.at(name1);
  const Graph& g2 = graphs.at(name2);
  Graph newGraph;
  graphs.insert(std::make_pair(newName, newGraph));
}

void duhanina::extract(std::istream& in, MapOfGraphs& graphs)
{
  std::string newName;
  std::string oldName;
  size_t count;
  in >> newName >> oldName >> count;
  if (graphs.find(newName) != graphs.end() || graphs.find(oldName) == graphs.end())
  {
    throw std::invalid_argument("Invalid command");
  }
  List< Graph::Vertex > vertices;
  for (size_t i = 0; i < count; ++i)
  {
    std::string v;
    in >> v;
    vertices.push_back(v);
  }
  graphs.insert(std::make_pair(newName, Graph()));
}
*/

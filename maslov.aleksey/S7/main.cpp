#include <iostream>
#include <unordered_map>
#include <fstream>
#include <functional>
#include <limits>
#include <algorithm>
#include "graph.hpp"

namespace
{
  void printBounds(std::ostream & out, std::vector< std::pair< std::string, int > > bounds)
  {
    for (auto it = bounds.begin(); it != bounds.end(); it++)
    {
      out << it->first << ' ' << it->second << '\n';
    }
  }
}

namespace maslov
{
  void getGraphs(std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {
    std::vector< std::string > graphNames;
    for (auto it = graphs.begin(); it != graphs.end(); it++)
    {
      graphNames.push_back(it->first);
    }
    if(graphNames.empty())
    {
      out << '\n';
    }
    std::sort(graphNames.begin(), graphNames.end());
    for (auto it = graphNames.begin(); it != graphNames.end(); it++)
    {
      out << *it << '\n';
    }
  }

  void getVertexes(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {
    std::string graphName;
    in >> graphName;
    Graph graph = graphs.at(graphName);
    std::vector< std::string > vertexes = graph.getVertexes();
    if (vertexes.empty())
    {
      out << '\n';
    }
    for (auto it = vertexes.begin(); it != vertexes.end(); it++)
    {
      out << *it << '\n';
    }
  }

  void getOutbound(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {
    std::string graphName, vertexName;
    in >> graphName >> vertexName;
    Graph graph = graphs.at(graphName);
    if (!graph.hasVertex(vertexName))
    {
      throw std::logic_error("ERROR: there is no such vertex");
    }
    auto outbounds = graph.getOutbound(vertexName);
    printBounds(out, outbounds);
  }

  void getInbound(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {
    std::string graphName, vertexName;
    in >> graphName >> vertexName;
    Graph graph = graphs.at(graphName);
    if (!graph.hasVertex(vertexName))
    {
      throw std::logic_error("ERROR: there is no such vertex");
    }
    auto inbounds = graph.getInbound(vertexName);
    printBounds(out, inbounds);
  }

  void createEdge(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {
    std::string graphName, v1, v2;
    int weight;
    in >> graphName >> v1 >> v2 >> weight;
    Graph graph = graphs.at(graphName);
    graph.addVertex(v1);
    graph.addVertex(v2);
    graph.addEdge(v1, v2, weight);
  }

  void deleteEdge(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {
    std::string graphName, v1, v2;
    int weight;
    in >> graphName >> v1 >> v2 >> weight;
    Graph graph = graphs.at(graphName);
    graph.deleteEdge(v1, v2, weight);
  }

  void createGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {
    std::string graphName;
    in >> graphName;
    if (graphs.find(graphName) != graphs.end())
    {
      throw std::logic_error("ERROR: such a graph already exists");
    }
    Graph newGraph;
    size_t vertexesCount = 0;
    in >> vertexesCount;
    std::string vertex;
    for (size_t i = 0; i < vertexesCount; i++)
    {
      in >> vertex;
      newGraph.addVertex(vertex);
    }
    graphs[graphName] = newGraph;
  }

  void mergeGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {
    std::string newGraphName, graphName1, graphName2;
    in >> newGraphName >> graphName1 >> graphName2;
    if (graphs.find(newGraphName) != graphs.end())
    {
      throw std::logic_error("ERROR: such a graph already exists");
    }
    Graph graph1 = graphs.at(graphName1);
    Graph graph2 = graphs.at(graphName2);
    Graph mergedGraph = graph1;
    mergedGraph.merge(graph2);
    graphs[newGraphName] = mergedGraph;
  }

  void extractGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {
    std::string newGraphName, graphName;
    in >> newGraphName >> graphName;
    if (graphs.find(newGraphName) != graphs.end())
    {
      throw std::logic_error("ERROR: such a graph already exists");
    }
    Graph graph = graphs.at(graphName);
    size_t countVertexes = 0;
    in >> countVertexes;
    std::set< std::string > vertexes;
    std::string vertex;
    for (size_t i = 0; i < countVertexes; ++i)
    {
      in >> vertex;
      graph.hasVertex(vertex);
      vertexes.insert(vertex);
    }
    Graph extractedGraph;
    extractedGraph.extract(graph, vertexes);
    graphs[newGraphName] = extractedGraph;
  }

  void readGraphs(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {
    std::string graphName;
    size_t edgeCount = 0;
    while (in >> graphName >> edgeCount)
    {
      Graph graph;
      for (size_t i = 0; i < edgeCount; ++i)
      {
        std::string vertexName1, vertexName2;
        int weight;
        in >> vertexName1 >> vertexName2 >> weight;
        graph.addEdge(vertexName1, vertexName2, weight);
      }
      graphs[graphName] = graph;
    }
  }
}

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "ERROR: wrong arguments\n";
    return 1;
  }
  std::ifstream fileInput(argv[1]);
  if (!fileInput.is_open())
  {
    std::cerr << "ERROR: cannot open the file\n";
    return 1;
  }

  std::unordered_map< std::string, maslov::Graph > graphs;
  std::unordered_map< std::string, std::function< void() > > cmds;
  cmds["graphs"] = std::bind(maslov::getGraphs, std::ref(std::cout), std::cref(graphs));
  cmds["vertexes"] = std::bind(maslov::getVertexes, std::ref(std::cin), std::ref(std::cout), std::cref(graphs));
  cmds["outbound"]  = std::bind(maslov::getOutbound, std::ref(std::cin), std::ref(std::cout), std::cref(graphs));
  cmds["inbound"] = std::bind(maslov::getInbound, std::ref(std::cin), std::ref(std::cout), std::cref(graphs));
  cmds["bind"] = std::bind(maslov::createEdge, std::ref(std::cin), std::ref(graphs));
  cmds["cut"] = std::bind(maslov::deleteEdge, std::ref(std::cin), std::ref(graphs));
  cmds["create"] = std::bind(maslov::createGraph, std::ref(std::cin), std::ref(graphs));
  cmds["merge"] = std::bind(maslov::mergeGraph, std::ref(std::cin), std::ref(graphs));
  cmds["extract"] = std::bind(maslov::extractGraph, std::ref(std::cin), std::ref(graphs));

  readGraphs(fileInput, graphs);
  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      cmds.at(command)();
    }
    catch (const std::exception &)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}

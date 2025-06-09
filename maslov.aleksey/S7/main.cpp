#include <iostream>
#include <unordered_map>
#include <fstream>
#include <functional>
#include <limits>
#include "graph.hpp"

namespace maslov
{
  void getGraphs(std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {}

  void getVertexes(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {}

  void getOutbound(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {}
  
  void getInbound(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs)
  {}

  void createEdge(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {}

  void deleteEdge(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {}

  void createGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {}

  void mergeGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {}

  void extractGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs)
  {}

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

  try
  {
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
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
  }
}

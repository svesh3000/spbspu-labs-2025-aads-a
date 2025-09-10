#include <fstream>
#include <iostream>
#include <functional>
#include "commands.hpp"
#include "graph.hpp"

std::unordered_map< std::string, sveshnikov::Graph > loadGraphs(char *filename);

int main(int argc, char **argv)
{
  using namespace sveshnikov;
  if (argc != 2)
  {
    std::cerr << "ERROR: File is not specified!" << '\n';
    return 1;
  }
  std::unordered_map< std::string, Graph > graph_map;
  try
  {
    graph_map = loadGraphs(argv[1]);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  std::unordered_map< std::string, std::function< void() > > cmds;
  cmds["graph"] = std::bind(graph);
  cmds["vertexes"] = std::bind(vertexes);
  cmds["outbound"] = std::bind(outbound);
  cmds["inbound"] = std::bind(inbound);
  cmds["bind"] = std::bind(bind);
  cmds["cut"] = std::bind(cut);
  cmds["create"] = std::bind(create);
  cmds["merge"] = std::bind(merge);
  cmds["extract"] = std::bind(extract);

  return 0;
}

std::unordered_map< std::string, sveshnikov::Graph > loadGraphs(char *filename)
{
  std::ifstream in(filename);
  if (!in.is_open())
  {
    throw std::runtime_error("ERROR: Cannot open file!");
  }

  std::unordered_map< std::string, sveshnikov::Graph > graph_map;
  std::string graph_name;
  size_t edges_count;
  while (in >> graph_name >> edges_count)
  {
    std::string vertex_name1, vertex_name2;
    unsigned int weight = 0;
    sveshnikov::Graph graph;
    for (size_t i = 0; i != edges_count; i++)
    {
      in >> vertex_name1 >> vertex_name2 >> weight;
      graph.add(std::make_pair(vertex_name1, vertex_name2), weight);
    }
    graph_map[graph_name] = graph;
  }
  if (!in.eof())
  {
    throw std::runtime_error("ERROR: Invalid data!");
  }
  return graph_map;
}

#include <fstream>
#include <iostream>
#include <functional>
#include <limits>
#include "commands.hpp"

sveshnikov::GraphsMap_t loadGraphs(char *filename);

int main(int argc, char **argv)
{
  using namespace sveshnikov;
  if (argc != 2)
  {
    std::cerr << "ERROR: File is not specified!" << '\n';
    return 1;
  }
  GraphsMap_t graph_map;
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

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)();
    }
    catch (const std::out_of_range &e)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  return 0;
}

sveshnikov::GraphsMap_t loadGraphs(char *filename)
{
  using namespace sveshnikov;
  std::ifstream in(filename);
  if (!in.is_open())
  {
    throw std::runtime_error("ERROR: Cannot open file!");
  }

  GraphsMap_t graph_map;
  std::string graph_name;
  size_t edges_count;
  while (in >> graph_name >> edges_count)
  {
    std::string vertex_name1, vertex_name2;
    unsigned int weight = 0;
    Graph graph;
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

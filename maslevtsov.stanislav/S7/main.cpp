#include <fstream>
#include <iostream>
#include <limits>
#include <hash_table/definition.hpp>
#include "graph.hpp"
#include "commands.hpp"

int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "<INVALID PARAMETERS NUMBER>\n";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "<INVALID DATA FILE>\n";
    return 1;
  }

  using namespace maslevtsov;

  graphs_map_t graphs;
  std::string graph_name;
  while ((fin >> graph_name) && !fin.eof()) {
    size_t edges_count = 0;
    fin >> edges_count;
    Graph graph;
    for (size_t i = 0; i < edges_count; ++i) {
      std::string vertice1, vertice2;
      unsigned weight = 0;
      fin >> vertice1 >> vertice2 >> weight;
      graph.bind(vertice1, vertice2, weight);
    }
    graphs[graph_name] = graph;
  }

  HashTable< std::string, std::function< void() > > commands;
  commands["graphs"] = std::bind(print_graphs, std::cref(graphs), std::ref(std::cout));
  commands["vertexes"] = std::bind(print_vertices, std::cref(graphs), std::ref(std::cin), std::ref(std::cout));
  commands["outbound"] = std::bind(print_outbound, std::cref(graphs), std::ref(std::cin), std::ref(std::cout));
  commands["inbound"] = std::bind(print_inbound, std::cref(graphs), std::ref(std::cin), std::ref(std::cout));
  commands["bind"] = std::bind(bind_vertices, std::ref(graphs), std::ref(std::cin));
  commands["cut"] = std::bind(cut_vertices, std::ref(graphs), std::ref(std::cin));
  commands["create"] = std::bind(create_graph, std::ref(graphs), std::ref(std::cin));
  commands["merge"] = std::bind(merge_graphs, std::ref(graphs), std::ref(std::cin));
  commands["extract"] = std::bind(extract_from_graph, std::ref(graphs), std::ref(std::cin));

  std::string command;
  while ((std::cin >> command) && !std::cin.eof()) {
    try {
      commands.at(command)();
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

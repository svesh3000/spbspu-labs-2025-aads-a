#include "commands.hpp"
#include <vector/definition.hpp>

void maslevtsov::print_graphs(const graphs_map_t& graphs, std::ostream& out)
{
  Tree< std::string, int > names;
  for (auto i = graphs.cbegin(); i != graphs.cend(); ++i) {
    names[i->first];
  }
  out << names.begin()->first;
  for (auto i = ++names.begin(); i != names.end(); ++i) {
    out << '\n' << i->first;
  }
}

void maslevtsov::print_vertices(const graphs_map_t& graphs, std::istream& in, std::ostream& out)
{
  std::string graph_name;
  in >> graph_name;
  Graph graph = graphs.at(graph_name);
  Tree< std::string, int > names = graph.get_vertices();
  out << names.begin()->first;
  for (auto i = ++names.begin(); i != names.end(); ++i) {
    out << '\n' << i->first;
  }
}

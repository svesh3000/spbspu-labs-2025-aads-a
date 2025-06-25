#include "graph_utils.hpp"

std::ifstream &abramov::readGraphs(std::ifstream &in, GraphCollection &collect)
{
  std::string name;
  size_t edges_count = 0;
  while(!in.eof())
  {
    in >> name >> edges_count;
    Graph graph(name);
    for (size_t i = 0; i < edges_count; ++i)
    {
      std::string vert_a;
      std::string vert_b;
      size_t w = 0;
      in >> vert_a >> vert_b >> w;
      graph.addEdge(vert_a, vert_b, w);
    }
    collect.addGraph(graph);
  }
  return in;
}

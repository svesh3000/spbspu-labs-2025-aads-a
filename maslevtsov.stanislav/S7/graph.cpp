#include "graph.hpp"

void maslevtsov::Graph::add_edge(const std::string& vertice1, const std::string& vertice2, unsigned weight)
{
  edges_set_[std::make_pair(vertice1, vertice2)].push_back(weight);
}

maslevtsov::Tree< std::string, int > maslevtsov::Graph::get_vertices() const
{
  Tree< std::string, int > vertices;
  for (auto i = edges_set_.cbegin(); i != edges_set_.cend(); ++i) {
    vertices[i->first.first];
    vertices[i->first.second];
  }
  return vertices;
}

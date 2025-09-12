#include "graph.hpp"

sveshnikov::Graph::Graph(const Graph &graph1, const Graph &graph2):
  graph_(graph1.graph_),
  vertexes_(graph1.vertexes_)
{
  for (auto i = graph2.graph_.begin(); i != graph2.graph_.end(); i++)
  {
    auto it = graph_.find(i->first);
    if (it != graph_.end())
    {
      auto list_edges = i->second;
      graph_[i->first].splice(graph_[i->first].cbefore_begin(), list_edges);
    }
    else
    {
      vertexes_[i->first.first];
      vertexes_[i->first.second];
      graph_[i->first] = i->second;
    }
  }
}

void sveshnikov::Graph::add_vertex(const std::string &vert)
{
  vertexes_[vert];
}

void sveshnikov::Graph::bind(const std::string &vert_out, const std::string &vert_in,
    unsigned weight)
{
  vertexes_[vert_out];
  vertexes_[vert_in];
  graph_[std::make_pair(vert_out, vert_in)].push_back(weight);
}

void sveshnikov::Graph::cut(const std::string &vert_out, const std::string &vert_in,
    unsigned int weight)
{
  auto edge_it = graph_.find(std::make_pair(vert_out, vert_in));
  if (edge_it == graph_.end())
  {
    throw std::out_of_range("ERROR: edge was not found!");
  }
  if (*edge_it->second.cbegin() == weight)
  {
    edge_it->second.erase(edge_it->second.cbegin());
    return;
  }
  for (auto i = ++edge_it->second.cbegin(); i != edge_it->second.cend(); i++)
  {
    if (*i == weight)
    {
      edge_it->second.erase(i);
      return;
    }
  }
  throw std::out_of_range("ERROR: edge with this weight was not found!");
}

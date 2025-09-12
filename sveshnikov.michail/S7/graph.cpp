#include "graph.hpp"

namespace
{
  void sort_weights(sveshnikov::Array< unsigned int > &weights);

  void sort_weights(sveshnikov::Array< unsigned int > &weights)
  {
    if (weights.empty())
    {
      return;
    }
    for (size_t i = 0; i < weights.getSize() - 1; i++)
    {
      for (size_t j = 0; j < weights.getSize() - i - 1; j++)
      {
        if (weights[j] > weights[j + 1])
        {
          std::swap(weights[j], weights[j + 1]);
        }
      }
    }
  }
}

sveshnikov::Graph::Graph(const Graph &graph1, const Graph &graph2):
  graph_(graph1.graph_),
  vertexes_(graph1.vertexes_)
{
  for (auto i = graph2.graph_.begin(); i != graph2.graph_.end(); i++)
  {
    if (graph_.find(i->first) != graph_.end())
    {
      for (size_t j = 0; j < i->second.getSize(); j++)
      {
        graph_[i->first].push_back(i->second[j]);
      }
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
  for (size_t i = 0; i != edge_it->second.getSize(); i++)
  {
    if (edge_it->second[i] == weight)
    {
      for (size_t j = i; j != edge_it->second.getSize() - 1; j++)
      {
        std::swap(edge_it->second[j], edge_it->second[j + 1]);
      }
      edge_it->second.pop_back();
      return;
    }
  }
  throw std::out_of_range("ERROR: edge with this weight was not found!");
}

sveshnikov::Array< std::string > sveshnikov::Graph::get_vertexes() const
{
  Array< std::string > verts;
  for (auto i = vertexes_.begin(); i != vertexes_.end(); i++)
  {
    verts.push_back(i->first);
  }
  return verts;
}

sveshnikov::AvlTree< std::string, sveshnikov::Array< unsigned int > >
    sveshnikov::Graph::get_outbounds(const std::string &vert) const
{
  AvlTree< std::string, sveshnikov::Array< unsigned int > > outbounds;
  for (auto i = graph_.begin(); i != graph_.end(); i++)
  {
    if (i->first.first == vert)
    {
      outbounds[i->first.second] = i->second;
      sort_weights(outbounds[i->first.second]);
    }
  }
}

sveshnikov::AvlTree< std::string, sveshnikov::Array< unsigned int > >
    sveshnikov::Graph::get_inbounds(const std::string &vert) const
{}

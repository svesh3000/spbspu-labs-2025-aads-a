#include "commands.hpp"
#include <iostream>

namespace
{
  void ioBound(const sveshnikov::AvlTree< std::string, sveshnikov::Array< unsigned int > > &bounds,
      std::ostream &out);

  void ioBound(const sveshnikov::AvlTree< std::string, sveshnikov::Array< unsigned int > > &bounds,
      std::ostream &out)
  {
    for (auto i = bounds.begin(); i != bounds.end(); i++)
    {
      out << i->first;
      for (size_t j = 0; j < i->second.getSize(); j++)
      {
        out << ' ' << i->second[j];
      }
      out << '\n';
    }
  }
}

void sveshnikov::graph(const GraphsMap_t &graph_map, std::ostream &out)
{
  if (graph_map.empty())
  {
    return;
  }
  for (auto it = graph_map.begin(); it != graph_map.end(); it++)
  {
    out << it->first << '\n';
  }
}

void sveshnikov::vertexes(const GraphsMap_t &graph_map, std::istream &in, std::ostream &out)
{
  std::string graph_name;
  in >> graph_name;
  Array< std::string > verts = graph_map.at(graph_name).get_vertexes();
  for (auto i = 0; i < verts.getSize(); i++)
  {
    out << verts[i] << '\n';
  }
}

void sveshnikov::outbound(const GraphsMap_t &graph_map, std::istream &in, std::ostream &out)
{
  std::string graph_name, vertex;
  in >> graph_name >> vertex;
  auto outbounds = graph_map.at(graph_name).get_outbounds(vertex);
  ioBound(outbounds, out);
}

void sveshnikov::inbound(const GraphsMap_t &graph_map, std::istream &in, std::ostream &out)
{
  std::string graph_name, vertex;
  in >> graph_name >> vertex;
  auto inbounds = graph_map.at(graph_name).get_inbounds(vertex);
  ioBound(inbounds, out);
}

void sveshnikov::bind(GraphsMap_t &graph_map, std::istream &in)
{}

void sveshnikov::cut(GraphsMap_t &graph_map, std::istream &in)
{}

void sveshnikov::create(GraphsMap_t &graph_map, std::istream &in)
{}

void sveshnikov::merge(GraphsMap_t &graph_map, std::istream &in)
{}

void sveshnikov::extract(GraphsMap_t &graph_map, std::istream &in)
{}

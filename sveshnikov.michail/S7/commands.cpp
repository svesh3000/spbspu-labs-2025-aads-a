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
  for (size_t i = 0; i < verts.getSize(); i++)
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
{
  std::string graph_name, vertex_out, vertex_in;
  unsigned int weight = 0;
  in >> graph_name >> vertex_out >> vertex_in >> weight;
  graph_map.at(graph_name).bind(vertex_out, vertex_in, weight);
}

void sveshnikov::cut(GraphsMap_t &graph_map, std::istream &in)
{
  std::string graph_name, vertex_out, vertex_in;
  unsigned int weight = 0;
  in >> graph_name >> vertex_out >> vertex_in >> weight;
  graph_map.at(graph_name).cut(vertex_out, vertex_in, weight);
}

void sveshnikov::create(GraphsMap_t &graph_map, std::istream &in)
{
  std::string graph_name;
  size_t count_k = 0;
  in >> graph_name >> count_k;
  if (graph_map.find(graph_name) != graph_map.end())
  {
    throw std::out_of_range("ERROR: this graph already exists!");
  }
  Graph graph;
  for (size_t i = 0; i < count_k; i++)
  {
    std::string vertex;
    in >> vertex;
    graph.add_vertex(vertex);
  }
  graph_map[graph_name] = graph;
}

void sveshnikov::merge(GraphsMap_t &graph_map, std::istream &in)
{
  std::string new_graph, old_graph1, old_graph2;
  in >> new_graph >> old_graph1 >> old_graph2;
  Graph graph(graph_map.at(old_graph1), graph_map.at(old_graph2));
  graph_map[new_graph] = graph;
}

void sveshnikov::extract(GraphsMap_t &graph_map, std::istream &in)
{
  std::string new_graph, old_graph;
  size_t count_k = 0;
  in >> new_graph >> old_graph >> count_k;
  Graph graph(graph_map.at(old_graph));
  for (size_t i = 0; i < count_k; i++)
  {
    std::string vertex;
    in >> vertex;
    graph.add_vertex(vertex);
  }
  graph_map[new_graph] = graph;
}

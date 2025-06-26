#include "graph_utils.hpp"

std::ifstream &abramov::readGraphs(std::ifstream &in, GraphCollection &collect)
{
  std::string name;
  size_t edges_count = 0;
  while(!in.eof())
  {
    if(!(in >> name >> edges_count))
    {
      break;
    }
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

void abramov::printVertSorted(const GraphCollection &collect, const std::string &name, std::ostream &out)
{
  const Graph &graph = collect.cgetGraph(name);
  SimpleArray< std::string > verts;
  HashTable< std::string, bool > uniq_verts;
  for (auto it = graph.cbegin(); it != graph.cend(); ++it)
  {
    const std::string &vert = it->first;
    if (uniq_verts.cfind(vert) == uniq_verts.cend())
    {
      uniq_verts.insert(vert, true);
      verts.pushBack(vert);
    }
    const SimpleArray< Edge > *edges = graph.getEdges(vert);
    if (edges)
    {
      for (size_t i = 0; i < edges->size(); ++i)
      {
        const std::string &vert = (*edges)[i].to;
        if (uniq_verts.cfind(vert) == uniq_verts.cend())
        {
          uniq_verts.insert(vert, true);
          verts.pushBack(vert);
        }
      }
    }
  }
  if (!verts.empty())
  {
    std::sort(&verts[0], &verts[0] + verts.size());
  }
  for (size_t i = 0; i < verts.size(); ++i)
  {
    out << verts[i] << "\n";
  }
}


#include "commands.hpp"

namespace
{
  using demehin::Tree;

  void printBounds(std::ostream& out, const Tree< std::string, Tree< unsigned int, size_t > > bounds)
  {
    for (auto it = bounds.begin(); it != bounds.end(); it++)
    {
      out << (*it).first;
      auto weights_it = (*it).second.begin();
      for(; weights_it != (*it).second.end(); weights_it++)
      {
        for (size_t i = 0; i < (*weights_it).second; i++)
        {
          out << " " << (*weights_it).first;
        }
      }
      out << "\n";
    }
  }

  void addEdges(demehin::Graph& gr, const demehin::Graph::Edges& edges)
  {
    for (const auto& edge : edges)
    {
      for (unsigned int weight : edge.second)
      {
        gr.addEdge(edge.first.first, edge.first.second, weight);
      }
    }
  }
}

void demehin::printGraphsNames(std::ostream& out, const MapOfGraphs& graphs)
{
  for (auto it = graphs.begin(); it != graphs.end(); it++)
  {
    out << (*it).first << "\n";
  }
}

void demehin::printVertexesNames(std::ostream& out, std::istream& in, const MapOfGraphs& graphs)
{
  std::string gr_name;
  in >> gr_name;
  Graph gr = graphs.at(gr_name);

  demehin::Tree< std::string, std::string > vrts = gr.getVrts();
  for (auto it = vrts.begin(); it != vrts.end(); it++)
  {
    out << (*it).first << "\n";
  }
}

void demehin::printOutbounds(std::ostream& out, std::istream& in, const MapOfGraphs& graphs)
{
  std::string gr_name, vrt_name;
  in >> gr_name >> vrt_name;

  Graph gr = graphs.at(gr_name);

  if (!gr.hasVrt(vrt_name))
  {
    throw std::logic_error("incorrect parameters");
  }

  auto outbounds = gr.getOutbounds(vrt_name);
  printBounds(out, outbounds);
}

void demehin::printInbounds(std::ostream& out, std::istream& in, const MapOfGraphs& graphs)
{
  std::string gr_name, vrt_name;
  in >> gr_name >> vrt_name;

  Graph gr = graphs.at(gr_name);

  if (!gr.hasVrt(vrt_name))
  {
    throw std::logic_error("incorrect parameters");
  }

  auto inbounds = gr.getInbounds(vrt_name);
  printBounds(out, inbounds);
}

void demehin::bind(std::istream& in, MapOfGraphs& graphs)
{
  std::string gr_name, from, to;
  unsigned int weight;
  in >> gr_name >> from >> to >> weight;

  graphs.at(gr_name).addEdge(from, to, weight);
}

void demehin::cut(std::istream& in, MapOfGraphs& graphs)
{
  std::string gr_name, from, to;
  unsigned int weight;
  in >> gr_name >> from >> to >> weight;

  if (!(graphs.at(gr_name).deleteEdge(from, to, weight)))
  {
    throw std::logic_error("incorrect parameters");
  }
}

void demehin::create(std::istream& in, MapOfGraphs& graphs)
{
  std::string gr_name;
  in >> gr_name;

  if (graphs.find(gr_name) != graphs.end())
  {
    throw std::logic_error("incorrect parameters");
  }

  graphs[gr_name];
}

void demehin::merge(std::istream& in, MapOfGraphs& graphs)
{
  std::string new_gr_name, gr1_name, gr2_name;
  in >> new_gr_name >> gr1_name >> gr2_name;
  if (graphs.find(gr1_name) == graphs.end() || graphs.find(gr2_name) == graphs.end() || graphs.find(new_gr_name) != graphs.end())
  {
    throw std::logic_error("incorrect parameters");
  }

  Graph res;

  auto g1 = graphs[gr1_name];
  auto edges1 = g1.getEdges();
  addEdges(res, edges1);

  auto g2 = graphs[gr2_name];
  auto edges2 = g2.getEdges();
  addEdges(res, edges2);

  graphs[new_gr_name] = res;
}

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
  Graph gr;
  try
  {
    gr = graphs.at(gr_name);
  }
  catch (const std::logic_error&)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

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

  Graph gr;
  try
  {
    gr = graphs.at(gr_name);
  }
  catch (const std::logic_error&)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  if (!gr.hasVrt(vrt_name))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  auto outbounds = gr.getOutbounds(vrt_name);
  printBounds(out, outbounds);
}

void demehin::printInbounds(std::ostream& out, std::istream& in, const MapOfGraphs& graphs)
{
  std::string gr_name, vrt_name;
  in >> gr_name >> vrt_name;

  Graph gr;
  try
  {
    gr = graphs.at(gr_name);
  }
  catch (const std::logic_error&)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  if (!gr.hasVrt(vrt_name))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  auto inbounds = gr.getInbounds(vrt_name);
  printBounds(out, inbounds);
}

void demehin::bind(std::ostream& out, std::istream& in, MapOfGraphs& graphs)
{
  std::string gr_name, from, to;
  unsigned int weight;
  in >> gr_name >> from >> to >> weight;

  Graph gr;
  try
  {
    graphs.at(gr_name).addEdge(from, to, weight);
  }
  catch (const std::logic_error&)
  {
    out << "<INVALID COMMAND>\n";
  }
}

void demehin::cut(std::ostream& out, std::istream& in, MapOfGraphs& graphs)
{
  std::string gr_name, from, to;
  unsigned int weight;
  in >> gr_name >> from >> to >> weight;
  Graph gr;
  try
  {
    if (!(graphs.at(gr_name).deleteEdge(from, to, weight)))
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
  }
  catch (const std::logic_error&)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
}

void demehin::create(std::ostream& out, std::istream& in, MapOfGraphs& graphs)
{
  std::string gr_name;
  in >> gr_name;

  if (graphs.find(gr_name) != graphs.end())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }

  graphs[gr_name];
}

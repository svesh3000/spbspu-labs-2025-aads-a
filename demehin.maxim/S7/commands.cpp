#include "commands.hpp"

void demehin::printGraphsNames(std::ostream& out, const MapOfGraphs graphs)
{
  for (auto it = graphs.begin(); it != graphs.end(); it++)
  {
    out << (*it).first << "\n";
  }
}

void demehin::printVertexesNames(std::ostream& out, std::istream& in, const MapOfGraphs graphs)
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

void demehin::printOutbounds(std::ostream& out, std::istream& in, const MapOfGraphs graphs)
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
  for (auto it = outbounds.begin(); it != outbounds.end(); it++)
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

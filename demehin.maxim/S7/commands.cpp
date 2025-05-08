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

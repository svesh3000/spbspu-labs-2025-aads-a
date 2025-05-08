#include "commands.hpp"

void demehin::printGraphsNames(std::ostream& out, const MapOfGraphs graphs)
{
  out << (*graphs.begin()).first;
  for (auto it = ++graphs.begin(); it != graphs.end(); it++)
  {
    out << "\n" << (*it).first;
  }
}

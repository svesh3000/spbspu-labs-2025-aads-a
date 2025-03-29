#include "tree_manips.hpp"

void demehin::print(std::ostream& out, std::istream& in, const MapOfTrees& mapOfTrees)
{
  std::string datasetName;
  in >> datasetName;
  TreeMap map = mapOfTrees.at(datasetName);
  if (map.empty())
  {
    out << "<EMPTY>\n";
  }

  out << datasetName;
  for (auto& key : map)
  {
    out << " " << key.first << " " << key.second;
  }
  out << "\n";
}

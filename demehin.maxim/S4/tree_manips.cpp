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

void demehin::complement(std::istream& in, MapOfTrees& mapOfTrees)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  TreeMap newMap;
  TreeMap map1;
  TreeMap map2;
  if (mapOfTrees.at(name1).size() > mapOfTrees.at(name2).size())
  {
    map1 = mapOfTrees.at(name1);
    map2 = mapOfTrees.at(name2);
  }
  else
  {
    map1 = mapOfTrees.at(name2);
    map2 = mapOfTrees.at(name1);
  }

  for (auto& key : map1)
  {
    if (map2.find(key.first) == map2.end())
    {
      newMap.insert(key);
    }
  }
  mapOfTrees.insert(std::make_pair(newName, newMap));
}

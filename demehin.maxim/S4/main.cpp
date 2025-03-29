#include <iostream>
#include <map>
#include <string>
#include <limits>

namespace
{
  using TreeMap = std::map< size_t, std::string >;
  using MapOfTrees = std::map< std::string, TreeMap >;

  void printTrees(std::ostream& out, const MapOfTrees& mapOfTrees)
  {
    for (auto& x : mapOfTrees)
    {
      out << x.first << " ";
      for (auto& y : x.second)
      {
        out << y.second << " ";
      }
      out << "\n";
    }
  }

  void inputTrees(std::istream& in, MapOfTrees& mapOfTrees)
  {
    while(!in.eof())
    {
      in.clear();
      TreeMap map;
      size_t key;
      std::string datasetName;
      in >> datasetName;
      while (in >> key)
      {
        std::string value;
        in >> value;
        map.insert(std::make_pair(key, value));
      }
      mapOfTrees.insert(std::make_pair(datasetName, map));
    }
  }
}

int main()
{
  MapOfTrees mapOfTrees;
  inputTrees(std::cin, mapOfTrees);
}

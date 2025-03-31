#include <iostream>
#include <map>
#include <string>
#include <limits>
#include "tree_manips.hpp"
#include <fstream>
#include <tree/tree.hpp>
#include <tree/node.hpp>

namespace
{
  using TreeMap = demehin::Tree< size_t, std::string >;
  using MapOfTrees = demehin::Tree< std::string, TreeMap >;

  /*void printTrees(std::ostream& out, const MapOfTrees& mapOfTrees)
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
  }*/

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

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    return 1;
  }

  std::ifstream file(argv[1]);
  MapOfTrees mapOfTrees;
  try
  {
    inputTrees(file, mapOfTrees);
  }
  catch (std::logic_error&)
  {
    std::cout << "input!\n";
    return 1;
  }
  std::string command;
  try
  {
    while (std::cin >> command)
    {
      if (command == "print")
      {
        demehin::print(std::cout, std::cin, mapOfTrees);
      }
      else if (command == "complement")
      {
        demehin::makeComplement(std::cin, mapOfTrees);
      }
      else if (command == "intersect")
      {
        demehin::makeIntersect(std::cin, mapOfTrees);
      }
      else if (command == "union")
      {
        demehin::makeUnion(std::cin, mapOfTrees);
      }
    }
  }
  catch (std::logic_error&)
  {
    std::cout << "command\n";
    return 1;
  }
}

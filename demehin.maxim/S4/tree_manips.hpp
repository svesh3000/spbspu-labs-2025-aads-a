#ifndef TREE_MANIPS
#define TREE_MANIPS
#include <string>
#include <map>
#include <iostream>

namespace demehin
{
  using TreeMap = std::map< size_t, std::string >;
  using MapOfTrees = std::map< std::string, TreeMap >;

  void print(std::ostream& out, std::istream& in, const MapOfTrees& mapOfTrees);
  void complement(std::istream& in, MapOfTrees& mapOfTrees);
}

#endif

#include <fstream>
#include <iostream>

#include "tree.hpp"

namespace {
  using TreeMap = zholobov::Tree< size_t, std::string >;
  using NamedTrees = zholobov::Tree< std::string, TreeMap >;

  NamedTrees readTrees(std::istream& input)
  {
    NamedTrees result;
    while (!input.eof()) {
      input.clear();
      TreeMap map;
      std::string datasetName;
      size_t key = 0;
      input >> datasetName;
      while (input.good()) {
        std::string value;
        input >> key >> value;
        if (input) {
          map.emplace(key, value);
        }
      }
      result.emplace(datasetName, map);
    }
    return result;
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Missed required parameter <filename>\n";
    return 1;
  }

  std::ifstream input_file(argv[1]);
  readTrees(input_file);
  // ...
}

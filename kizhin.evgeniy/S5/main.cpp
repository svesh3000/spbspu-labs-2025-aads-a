#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "map-utils.hpp"

int main(int argc, char** argv)
{
  if (argc != 3 || argv[2][0] == '\0') {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " <ascending|descending|breadth> <filename>";
    return 1;
  }
  const char* filename = argv[2];
  using namespace kizhin;
  try {
    std::fstream in(filename);
    if (!in.is_open()) {
      std::cerr << "Failed to open file: " << filename << '\n';
      return 1;
    }
    MapT map;
    if (!(in >> map)) {
      std::cout << "<EMPTY>\n";
      return 0;
    }
    ValueCollector result;
    if (std::strcmp(argv[1], "ascending") == 0) {
      result = map.traverseLmr(result);
    } else if (std::strcmp(argv[1], "descending") == 0) {
      result = map.traverseRml(result);
    } else if (std::strcmp(argv[1], "breadth") == 0) {
      result = map.traverseBreadth(result);
    } else {
      throw std::logic_error("Invalid traverse type given");
    }
    std::cout << result.keys << ' ' << result.values << '\n';
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
}


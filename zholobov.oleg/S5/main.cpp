#include <fstream>
#include <iostream>

#include <tree/tree.hpp>

namespace {

  using TreeMap = zholobov::Tree< int, std::string >;

  TreeMap readTree(std::istream& input)
  {
    TreeMap result;
    TreeMap::key_type key{};
    TreeMap::mapped_type value{};
    while (input >> key >> value) {
      result.emplace(key, value);
    }
    return result;
  }

}

int main(int argc, char* argv[])
{
  if (argc != 3) {
    std::cerr << "Error in parameters. Run as ./lab [ascending|descending|breadth] filename\n";
    return 1;
  }
  std::string traversal{argv[1]};
  std::ifstream input_file(argv[2]);
  TreeMap map = readTree(input_file);

  if (traversal == "ascending") {
  } else if (traversal == "descending") {
  } else if (traversal == "breadth") {
  } else {
    std::cerr << "Invalid 1st parameter. Use one of [ascending|descending|breadth]\n";
    return 1;
  }
}

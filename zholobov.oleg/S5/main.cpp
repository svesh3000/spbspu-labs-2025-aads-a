#include <fstream>
#include <iostream>

#include <tree/tree.hpp>
#include "key_sum.hpp"

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
  if (!input_file) {
    std::cerr << "Error opening file\n";
    return 1;
  }
  TreeMap map = readTree(input_file);
  if (map.empty()) {
    std::cout << "<EMPTY>\n";
    return 0;
  }

  try {
    zholobov::KeySum key_sum;
    if (traversal == "ascending") {
      key_sum = map.traverse_lnr(key_sum);
    } else if (traversal == "descending") {
      key_sum = map.traverse_rnl(key_sum);
    } else if (traversal == "breadth") {
      key_sum = map.traverse_breadth(key_sum);
    } else {
      std::cerr << "Invalid 1st parameter. Use one of [ascending|descending|breadth]\n";
      return 1;
    }
    std::cout << key_sum.sum_ << key_sum.values_ << "\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}

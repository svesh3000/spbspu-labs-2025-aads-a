#include <fstream>
#include <iostream>

namespace {
  void readTrees(std::istream& input)
  {
    if (input) {
      std::cout << "Reading trees...\n";
    }
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

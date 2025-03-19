#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  std::ifstream inputFile;
  if (argc > 1) {
    inputFile.open(argv[1]);
    if (!inputFile.is_open()) {
      std::cerr << "Error! Invalid openong file!\n";
      return 1;
    }
  }
  std::istream& in = (argc > 1) ? inputFile : std::cin;
  std::string line;
  while (getline(in, line)) {
    if (line.empty()) {
      continue;
    }
  }
  if (!in) {
  }
}
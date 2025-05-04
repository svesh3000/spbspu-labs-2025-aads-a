#include <iostream>
#include <fstream>
#include <limits>
#include "map_operations.hpp"
#include <tree/definition.hpp>

int main(int argc, char** argv)
{
  using namespace maslevtsov;

  if (argc != 2) {
    std::cerr << "<INVALID PARAMETERS>\n";
    return 1;
  }
  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "<INVALID DATA FILE>\n";
    return 1;
  }
  setmap_t data_map;
  input_setmap(fin, data_map);

  commands_t commands;
  fill_with_commands(commands);
  std::string command;
  while (std::cin) {
    std::cin >> command;
    if (std::cin.eof()) {
      break;
    }
    try {
      commands.at(command)(std::cin, data_map);
    } catch (...) {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

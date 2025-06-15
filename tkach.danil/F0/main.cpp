#include <iostream>
#include <fstream>
#include <limits>
#include <cstddef>
#include <map>
#include <functional>
#include <AVLtree.hpp>
#include <list.hpp>
#include "commands.hpp"

int main(const int argc, const char* const* const argv)
{
  using namespace tkach;
  if (argc != 1)
  {
    std::cerr << "<ERROR: INCORRECT INPUT>\n" << argv[0];
    return 1;
  }
  using namespace std::placeholders;
  AvlTree< std::string, AvlTree< std::string, List< std::string > > > data;
  std::map< std::string, std::function< void() > > cmds;
  cmds["import"] = std::bind(import, std::ref(std::cin), std::ref(data));
  cmds["addword"] = std::bind(addWord, std::ref(std::cin), std::ref(data));
  cmds["printall"] = std::bind(printAll, std::ref(std::cout), std::cref(data));
  cmds["removeword"] = std::bind(removeWord, std::ref(std::cin), std::ref(data));
  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      cmds.at(command)();
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}

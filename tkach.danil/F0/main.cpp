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
  if (argc != 2)
  {
    std::cerr << "<ERROR: INCORRECT INPUT\n";
    return 1;
  }
  std::fstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "<FILE IS NOT OPEN>\n";
    return 1;
  }
  using namespace std::placeholders;
  AvlTree< std::string, AvlTree< std::string, List < std::string > > > data = inputDataSets(in);
  if (!in || !in.eof())
  {
    std::cerr << "Error: incorrect input\n";
    return 1;
  }
  std::map< std::string, std::function< void() > > cmds;
  cmds["graphs"] = std::bind(printGraphs, std::ref(std::cout), std::cref(data));
  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      cmds.at(command)();
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
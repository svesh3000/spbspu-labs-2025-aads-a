#include <iostream>
#include <fstream>
#include <functional>
#include <unordered_map>
#include "graph.hpp"
#include "graph-commands.hpp"

int main(int argc, char** argv)
{
  using namespace alymova;
  using GraphsSet = std::unordered_map< std::string, Graph >;
  using CommandsSet = std::unordered_map< std::string, std::function< void(const GraphsSet&) > >;

  if (argc != 2)
  {
    std::cerr << "<INCORRECT ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "<INCORRECT FILE>\n";
    return 1;
  }

  try
  {
    GraphsSet graphs = readGraphsFile(file);
    file.clear();

    CommandsSet commands = complectCommands(std::cin, std::cout);
    std::string command;
    while (std::cin >> command)
    {
      try
      {
        commands.at(command)(graphs); 
      }
      catch (const std::exception& e)
      {
        std::cerr << "<INVALID COMMAND>\n";
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}


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

  /*std::string name;
  while (file >> name)
  {
    Graph gr;
    file >> gr;
    if (file)
    {
      graphs.insert(std::make_pair(name, gr));
    }
  }
  if (!file.eof() && file.fail())
  {
    std::cerr << "<INCORRECT GRAPHS DESCRIPTION>\n";
    return 1;
  }*/

  try
  {
    GraphsSet graphs = readGraphsFile(file);
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
  /*for (auto it = graphs.begin(); it != graphs.end(); ++it)
  {
    std::cout << it->first << '\n' << it->second << '\n';
  }*/
}


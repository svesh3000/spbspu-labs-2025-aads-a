#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <unordered_map>
#include "graph.hpp"
#include "graph-commands.hpp"
#include "hash-table.hpp"
#include "hash-functions.hpp"

int main(int argc, char** argv)
{
  using namespace alymova;
  //using GraphsSet = std::unordered_map< std::string, Graph >;
  //using CommandsSet = std::unordered_map< std::string, std::function< void(GraphsSet&) > >;
  using GraphsSet = HashTable< std::string, Graph >;
  using CommandsSet = HashTable< std::string, std::function< void(GraphsSet&) > >;

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
    while (!(std::cin >> command).eof())
    {
      try
      {
        commands.at(command)(graphs);
        if (command == "graphs" || command == "vertexes" || command == "outbound" || command == "inbound")
        {
          std::cout << '\n';
        }
      }
      catch (const std::exception& e)
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  /*HashTable< int, std::string > table;
  std::pair< int, std::string > p1(1, "fffff");
  std::pair< int, std::string > p2(1, "vvvvv");
  std::pair< int, std::string > p3(3, "vvvvv");
  std::pair< int, std::string > p4(45, "vvvvv");
  std::pair< int, std::string > p5(12, "vvvvv");
  table.insert(p1);
  table.insert(p2);
  table.insert(p3);
  table.insert(p4);
  table.insert(p5);
  table.erase(table.begin(), table.end());
  for (size_t i = 3; i < 20; i++)
  {
    std::pair< int, std::string > p(i, "gggg");
    table.insert(p);
  }
  for (auto it = table.begin(); it != table.end(); it++)
  {
    std::cout << it->first << '\n';
  }*/
}


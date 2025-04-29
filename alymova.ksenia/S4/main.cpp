#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <map>
#include <functional>
#include "utils.hpp"
#include "tree-2-3.hpp"
#include "tree-node.hpp"
#include "tree-const-iterator.hpp"

int main(int argc, char** argv)
{
  using namespace alymova;
  using Dataset_t = std::map< size_t, std::string, std::less< size_t > >;
  using CompositeDataset_t = std::map< std::string, Dataset_t, std::less< std::string > >;
  using CommandDataset_t = std::map<
    std::string,
    std::function< void(CompositeDataset_t&) >,
    std::less< std::string >
  >;

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
    CompositeDataset_t dataset_comp = readDictionaryFile(file);
    file.clear();

    CommandDataset_t dataset_commands = complectCommands();
    std::string command;
    while ((std::cin >> command))
    {
      dataset_commands.at(command)(dataset_comp);
      if (command == "print")
      {
        std::cout << '\n';
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}

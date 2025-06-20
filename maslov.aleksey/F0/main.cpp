#include <iostream>
#include <string>
#include <fstream>
#include <hashTable/hashTable.hpp>
#include <functional>
#include <limits>
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace maslov;
  if (std::string(argv[1]) == "--help")
  {
    printHelp(std::cout);
    return 0;
  } 
  if (argc != 3)
  {
    std::cerr << "ERROR: wrong arguments\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "ERROR: cannot open the file\n";
    return 1;
  }
  HashTable< std::string, HashTable< std::string, int > > dicts;
  try
  {
    dicts[argv[2]] = HashTable< std::string, int >{};
    loadFromFile(file, argv[2], dicts);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
  }
  HashTable< std::string, std::function< void() > > cmds;
  cmds["createdictionary"] = std::bind(createDictionary, std::ref(std::cin), std::ref(dicts));
  cmds["showdictionary"] = std::bind(showDictionary, std::ref(std::cout), std::cref(dicts));
  cmds["load"] = std::bind(load, std::ref(std::cin), std::ref(dicts));
  cmds["union"] = std::bind(unionDictionary, std::ref(std::cin), std::ref(dicts));
  cmds["intersect"] = std::bind(intersectDictionary, std::ref(std::cin), std::ref(dicts));
  cmds["copy"] = std::bind(copyDictionary, std::ref(std::cin), std::ref(dicts));
  cmds["addword"] = std::bind(addWord, std::ref(std::cin), std::ref(dicts));
  cmds["size"] = std::bind(printSize, std::ref(std::cin), std::ref(std::cout), std::cref(dicts));
  cmds["cleanword"] = std::bind(cleanWord, std::ref(std::cin), std::ref(dicts));
  cmds["cleandictionary"] = std::bind(cleanDictionary, std::ref(std::cin), std::ref(dicts));
  cmds["top"] = std::bind(printTop, std::ref(std::cin), std::ref(std::cout), std::cref(dicts));
  cmds["rare"] = std::bind(printRare, std::ref(std::cin), std::ref(std::cout), std::cref(dicts));
  cmds["frequency"] = std::bind(printFrequency, std::ref(std::cin), std::ref(std::cout), std::cref(dicts));
  cmds["wordRange"] = std::bind(createWordRange, std::ref(std::cin), std::ref(dicts));
  std::string command;
  while (!(std::cin >> command).eof())
  {
    try
    {
      cmds.at(command)();
    }
    catch (const std::exception & e)
    {
     std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << e.what() << '\n';
    }
  }
}

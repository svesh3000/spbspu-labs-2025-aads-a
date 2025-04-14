#include <cstddef>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include "commands.hpp"
using namespace kiselev;

namespace
{
  void input(std::istream& in, dataset& dictionary)
  {
    std::string name;
    std::string value;
    size_t key;
    while (in >> name)
    {
      data tree;
      if (in.get() == '\n')
      {
        dictionary.insert(std::make_pair(name, tree));
        continue;
      }
      while (in >> key >> value)
      {
        tree.insert(std::make_pair(key, value));
        if (in.get() == '\n')
        {
          break;
        }
      }
      dictionary.insert(std::make_pair(name, tree));
    }
  }
}
int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Invalid parameters\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  dataset dictionary;
  try
  {
    input(file, dictionary);
  }
  catch (const std::exception&)
  {
    std::cerr << "Error during input\n";
    return 1;
  }
  RBTree< std::string, std::function< void() > > commands;
  commands.insert(std::make_pair("print", [&](){ print(std::cout, std::cin, dictionary); }));
  commands.insert(std::make_pair("complement", [&](){ complement(std::cin, dictionary); }));
  commands.insert(std::make_pair("intersect", [&](){ intersect(std::cin, dictionary); }));
  commands.insert(std::make_pair("union", [&](){ unite(std::cin, dictionary); }));
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)();
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

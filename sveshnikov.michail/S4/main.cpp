#include <fstream>
#include "dict-utils.hpp"

int main(int argc, char **argv)
{
  using Dict_t = std::map< int, std::string >;
  using DataTree_t = std::map< std::string, Dict_t >;
  using CommandHolder_t =
      std::map< std::string, std::function< void(std::istream &, DataTree_t &) > >;
  if (argc != 2)
  {
    std::cerr << "ERROR: the file is not specified!" << '\n';
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "ERROR: Cannot open file!" << '\n';
    return 1;
  }

  CommandHolder_t comand_holder;
  DataTree_t dictionary_tree;
  try
  {
    comand_holder = getCommands();
    dictionary_tree = loadDicts(in);
  }
  catch (const std::bad_alloc &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      comand_holder.at(command)(in, dictionary_tree);
    }
    catch (const std::exception &e)
    {
      std::cerr << "INVALID COMMAND" << '\n';
    }
    if (command == "print")
    {
      std::cout << '\n';
    }
  }
  return 0;
}

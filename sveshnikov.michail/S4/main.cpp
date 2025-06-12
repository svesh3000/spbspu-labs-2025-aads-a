#include "dict-utils.hpp"

int main(int argc, char **argv)
{
  using namespace sveshnikov;
  if (argc != 2)
  {
    std::cerr << "ERROR: the file is not specified!" << '\n';
    return 1;
  }

  CommandHolder_t comand_holder;
  DataTree_t dictionary_tree;
  try
  {
    comand_holder = getCommands();
    dictionary_tree = loadDicts(argv[1]);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      comand_holder.at(command)(std::cin, dictionary_tree);
    }
    catch (const std::out_of_range &e)
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    if (command == "print")
    {
      std::cout << '\n';
    }
  }
  return 0;
}

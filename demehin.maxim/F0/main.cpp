#include <iostream>
#include <fstream>
#include <cstring>
#include <tree/tree.hpp>
#include <list/list.hpp>
#include "commands.hpp"

namespace
{
  using list_t = demehin::List< std::string >;
  using tree_t = demehin::Tree< std::string, list_t >;
  using dict_t = demehin::Tree< std::string, tree_t >;

  void inputDict(std::istream& in, dict_t& dicts)
  {
    std::string dict_name;
    while (std::getline(in, dict_name))
    {
      if (dict_name.empty())
      {
        continue;
      }

      tree_t current_dict;
      while (in.peek() != '\n' && in.peek() != EOF)
      {
        std::string key;
        in >> key;

        list_t translations;
        std::string val;
        while (in >> val)
        {
          translations.push_back(val);
          if (in.peek() == '\n')
          {
            break;
          }
        }

        current_dict.insert(std::make_pair(key, translations));
        if (in.peek() == '\n')
        {
          in.get();
        }
      }
      dicts.insert(std::make_pair(dict_name, current_dict));
    }
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "ERROR: invalid number of parameters";
    return 1;
  }

  if (std::string(argv[1]) == "--help")
  {
    demehin::printHelp(std::cout);
    return 0;
  }

  std::ifstream file(argv[1]);
  dict_t dicts;
  try
  {
    inputDict(file, dicts);
  }
  catch (...)
  {
    std::cerr << "Input error\n";
    return 1;
  }
}

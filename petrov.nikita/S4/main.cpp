#include <fstream>
#include <map>
#include <string>
#include <iostream>

namespace
{
  int checkArguments(const int argc);

  int checkArguments(const int argc)
  {
    if (argc == 2)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

int main(int argc, const char * const * argv)
{
  using subtree_t = std::map< int, std::string, std::less< int > >;
  using maintree_t = std::map< std::string, subtree_t >;
  maintree_t tree;
  subtree_t subtree;
  std::ifstream input(argv[1]);
  if (!checkArguments(argc))
  {
    std::cerr << "ERROR: Incorrect number of arguments";
    std::cerr << "\n";
    return 1;
  }
  while (!input.eof())
  {
    std::string dataset;
    input >> dataset;
    if (input.eof())
    {
      break;
    }
    else if (dataset.empty())
    {
      continue;
    }
    std::pair< int, std::string > data;
    while (input)
    {
      input >> data.first;
      input >> data.second;
      if (!input)
      {
        input.clear();
        break;
      }
      subtree.insert({ data.first, data.second });
    }
    tree.insert({ dataset, subtree });
  }
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    std::cout << it->first << " dictionary:" << "\n";
    for (auto sub_it = it->second.cbegin(); sub_it != it->second.cend(); ++sub_it)
    {
      std::cout << (*sub_it).first << " => " << (*sub_it).second << "\n";
    }
  }
}

#include <iostream>
#include <fstream>
#include <avl_tree.hpp>

namespace
{
  int checkArguments(const int argc);

  int checkArguments(const int argc)
  {
    if (argc == 3)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

int main(const int argc, const char * const * argv)
{
  using namespace petrov;
  if (!checkArguments(argc))
  {
    std::cerr << "ERROR: Invalid number of command line arguments";
    std::cerr << '\n';
    return 1;
  }
  AVLTree< int, std::string > tree;
  std::ifstream in(argv[2]);
  while (!in.eof())
  {
    int key = 0;
    std::string val;
    if (in >> key >> val)
    {
      tree.insert({ key, val });
    }
  }
}

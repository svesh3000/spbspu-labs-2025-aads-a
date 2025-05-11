#include <fstream>
#include <iostream>
#include <two-three-tree.h>
#include "key-adder.hpp"

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "ERROR: Invalid number of arguments\n";
    return 1;
  }

  std::string treverse_mode(argv[1]);
  std::string filename(argv[2]);

  using namespace savintsev;

  TwoThreeTree< long long, std::string > tree;

  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << "ERROR: Can't open file\n";
    return 1;
  }

  long long key;
  std::string value;
  while (file >> key >> value)
  {
    tree.insert({key, value});
  }

  if (tree.empty())
  {
    std::cout << "<EMPTY>\n";
    return 0;
  }

  try
  {
    KeyAdder summator;

    if (treverse_mode == "ascending")
    {
      //tree.traverse_lnr(summator);
    }
    else if (treverse_mode == "descending")
    {
      //tree.traverse_rnl(summator);
    }
    else if (treverse_mode == "breadth")
    {
      //tree.traverse_breadth(summator);
    }
    else
    {
      std::cerr << "ERROR: Traverse doesn't exist (Invalid argument)\n";
      return 1;
    }

    std::cout << summator.result_ << summator.values_ << "\n";
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << "ERROR: " << e.what() << "\n";
    return 1;
  }
}

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include "tree.hpp"
#include "keySum.hpp"
int main(int argc, char** argv)
{
  using namespace kiselev;
  if (argc != 3)
  {
    std::cerr << "Invalid parameters\n";
    return 1;
  }
  std::ifstream file(argv[2]);
  RBTree< int, std::string > tree;
  std::pair< int, std::string > value;
  while (file >> value.first >> value.second)
  {
    tree.insert(value);
  }
  if (!file.eof())
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }
  if (tree.empty())
  {
    std::cout << "<EMPTY>\n";
  }
  else
  {
    KeySum funct;
    std::string direction(argv[1]);
    try
    {
      if (direction == "ascending")
      {
        funct = tree.traverse_lnr(funct);
      }
      else if (direction == "descending")
      {
        funct = tree.traverse_rnl(funct);
      }
      else if (direction == "breadth")
      {
        funct = tree.traverse_breadth(funct);
      }
      else
      {
        throw std::logic_error("Incorrect direction");
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
    std::cout << funct.sum << funct.str << "\n";
    return 0;
  }
}

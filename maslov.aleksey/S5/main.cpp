#include <fstream>
#include <iostream>
#include <tree.hpp>
#include "keySum.hpp"

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "ERROR: wrong arguments\n";
    return 1;
  }
  std::ifstream fileInput(argv[1]);
  if (!fileInput.is_open())
  {
    std::cerr << "ERROR: cannot open the file\n";
    return 1;
  }
  int key = 0;
  std::string value;
  maslov::BiTree< int, std::string, std::less< int > > biTree;
  while ((fileInput >> key >> value) && !fileInput.eof())
  {
    biTree.push(key, value);
  }
  if (biTree.empty())
  {
    std::cout << "<EMPTY>\n";
    return 0;
  }
  try
  {
    std::string cmd(argv[1]);
    maslov::KeySum keySum;
    if (cmd == "ascending")
    {
      biTree.traverseLnr(keySum);
    }
    else if (cmd == "descending")
    {
      biTree.traverseRnl(keySum);
    }
    else if (cmd == "breadth")
    {
      biTree.traverseBreadth(keySum);
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      return 1;
    }
    std::cout << keySum.key << ' ' << keySum.value << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

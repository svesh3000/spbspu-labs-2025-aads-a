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
    maslov::KeyValueAccumulator result;
    if (cmd == "ascending")
    {
      biTree.traverseLnr(result);
    }
    else if (cmd == "descending")
    {
      biTree.traverseRnl(result);
    }
    else if (cmd == "breadth")
    {
      biTree.traverseBreadth(result);
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      return 1;
    }
    std::cout << result.keySum << ' ' << result.values << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}

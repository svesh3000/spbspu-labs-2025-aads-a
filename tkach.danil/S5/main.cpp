#include <iostream>
#include <fstream>
#include <AVLtree.hpp>
namespace
{

}

int main(const int argc, const char* const* const argv)
{
  using namespace tkach;
  if (argc != 3)
  {
    std::cerr << "Error: incorrect input\n";
    return 1;
  }
  std::fstream in(argv[2]);
  if (!in.is_open())
  {
    std::cerr << "File is not open\n";
    return 1;
  }
  int key = 0;
  std::string value;
  AvlTree< int, std::string > tree;
  while (in >> key >> value)
  {
    tree.insert(std::make_pair(key, value));
  }
  if (!in.eof())
  {
    std::cerr << "Error: incorrect input\n";
    return 1;
  }
  if (tree.empty())
  {
    std::cout << "EMPTY\n";
    return 0;
  }
  std::string cmd = argv[1];
  try
  {
    if (command == "ascending")
    {

    }
    else if (command == "ascending")
    {

    }
    else if (command == "ascending")
    {

    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      return 1;
    }
  }
}

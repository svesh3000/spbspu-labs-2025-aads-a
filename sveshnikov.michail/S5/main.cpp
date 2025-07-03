#include <fstream>
#include <iostream>
#include <functional>
#include <tree/tree.hpp>
#include "kv-aggregator.hpp"

sveshnikov::AvlTree< int, std::string > loadData(char *filename);

int main(int argc, char **argv)
{
  using namespace sveshnikov;
  if (argc != 3)
  {
    std::cerr << "Error: Not enough parameters!\n";
    return 1;
  }
  AvlTree< int, std::string > data;
  try
  {
    data = loadData(argv[2]);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}

sveshnikov::AvlTree< int, std::string > loadData(char *filename)
{
  using namespace sveshnikov;
  std::ifstream in(filename);
  if (!in.is_open())
  {
    throw std::runtime_error("ERROR: Cannot open file!");
  }
  AvlTree< int, std::string > data;
  int key = 0;
  std::string value;
  while (in >> key >> value)
  {
    data[key] = value;
  }
  if (!in.eof())
  {
    throw std::runtime_error("ERROR: Incorrect input!");
  }
  return data;
}

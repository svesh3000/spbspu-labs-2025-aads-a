#include "commands.hpp"
#include <iostream>
#include <fstream>
using namespace kiselev;

namespace
{
  void input(std::istream& in, dataset& dictionary)
  {
    while (in)
    {
      std::string name;
      in >> name;
      data tree;
      size_t key;
      std::string value;
      while (in && in.peek() != '\n')
      {
        in >> key >> value;
        tree.insert(std::make_pair(key, value));
      }
      dictionary.insert(std::make_pair(name, tree));
    }
  }
}
int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Invalid parameters\n";
  }
  std::ifstream file(argv[1]);
  dataset dictionary;
  input(file, dictionary);
}

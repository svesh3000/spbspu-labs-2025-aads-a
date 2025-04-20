#include <iostream>
#include <fstream>
#include <cstddef>
#include "AVLtree.hpp"
#include "commands.hpp"

namespace
{
  tkach::AvlTree< std::string, tkach::AvlTree< size_t, std::string > > inputDataSets(std::istream& in)
  {
    using namespace tkach;
    tkach::AvlTree< std::string, tkach::AvlTree< size_t, std::string > > fulldata;
    while(!in.eof())
    {
      AvlTree< size_t, std::string > temp;
      std::string name;
      in >> name;
      size_t key = 0;
      std::string value;
      char c = '\0';
      while(in.get(c) && c != '\n')
      {
        in >> key >> value;
        temp.insert(std::make_pair(key, value));
      }
      fulldata.insert(std::make_pair(name, temp));
    }
    return fulldata;
  }
}

int main()
{
  using namespace tkach;
  // if (argc != 2)
  // {
  //   std::cerr << "Error: incorrect input\n";
  //   return 1;
  // }
  // std::fstream in2(argv[1]);
  std::fstream in("/home/danil//spbspu-labs-2025-aads-a/tkach.danil/S4/input.txt");
  if (!in.is_open())
  {
    std::cerr << "File is not open\n";
    return 1;
  }
  AvlTree< std::string, AvlTree< size_t, std::string > > data = inputDataSets(in);
  print(std::cin, data, std::cout);
  return 0;
}

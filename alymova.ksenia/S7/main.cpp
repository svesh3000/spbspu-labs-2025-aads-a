#include <iostream>
#include <fstream>
#include <unordered_map>
#include "graph.hpp"

int main(int argc, char** argv)
{
  using namespace alymova;

  if (argc != 2)
  {
    std::cerr << "<INCORRECT ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "<INCORRECT FILE>\n";
    return 1;
  }

  std::unordered_map< std::string, Graph > graphs;
  std::string name;
  while (file >> name)
  {
    Graph gr;
    file >> gr;
    if (file)
    {
      graphs.insert(std::make_pair(name, gr));
    }
  }
  if (!file.eof())
  {
    std::cerr << "<INCORRECT GRAPHS DESCRIPTION>\n";
    return 1;
  }
  for (auto it = graphs.begin(); it != graphs.end(); ++it)
  {
    std::cout << it->first << '\n' << it->second << '\n';
  }
}


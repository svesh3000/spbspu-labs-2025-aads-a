#include <fstream>
#include <iostream>
#include "graph.hpp"
#include "commands.hpp"
#include <tree/tree.hpp>

namespace
{
  using MapOfGraphs = demehin::Tree< std::string, demehin::Graph >;

  void inputGraphs(std::istream& in, MapOfGraphs& graphs)
  {
    std::string name;
    while (in >> name)
    {
      size_t cnt;
      demehin::Graph gr;
      in >> cnt;
      for (size_t i = 0; i < cnt; i++)
      {
        std::string from, to;
        unsigned int weight;
        in >> from >> to >> weight;
        gr.addEdge(from, to, weight);
      }
      graphs[name] = gr;
    }
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    return 1;
  }

  std::ifstream file(argv[1]);
  MapOfGraphs mapOfGraphs;
  inputGraphs(file, mapOfGraphs);

  demehin::printGraphsNames(std::cout, mapOfGraphs);
  std::cout << "\n";
}

#include <fstream>
#include <iostream>
#include "graph.hpp"
#include <tree/tree.hpp>

namespace
{
  using MapOfGraphs = demehin::Tree< std::string, demehin::Graph >;

  void inputGraphs(std::istream& in, MapOfGraphs& graphs)
  {
    while (!in.eof())
    {
      in.clear();
      std::string name;
      size_t cnt;
      demehin::Graph gr;
      in >> name >> cnt;
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

  mapOfGraphs["gr1"].print();
  std::cout << "\n";
}

#include <iostream>
#include "graph_utils.hpp"

int main(int argc, char **argv)
{
  using namespace abramov;

  if (argc != 2)
  {
    std::cerr << "Wrong parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Incorrect filename\n";
    return 1;
  }
  GraphCollection collection{};
  readGraphs(input, collection);
  collection.printAllGraphs(std::cout);
  std::string s = "gr1";
  printVertsSorted(collection, s, std::cout);
  std::string v1 = "c";
  std::string v2 = "b";
  printOutVerts(collection, s, v1, std::cout);
//  printInVerts(collection, s, v2, std::cout);
}

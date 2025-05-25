#include <iostream>
#include <fstream>
#include "inputTrees.hpp"

int main()
{
  smirnov::TreeOfTrees trees;
  std::ifstream file("test.txt");
  smirnov::inputTrees(trees, file);
  for (const auto & dict : trees)
   {
    std::cout << "Dictionary: " << dict.first << std::endl;
  }
}

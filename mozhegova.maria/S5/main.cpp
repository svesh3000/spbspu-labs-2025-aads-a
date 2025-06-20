#include <iostream>
#include <fstream>
#include <tree.hpp>
#include "key_summ.hpp"

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "wrong arguments\n";
    return 1;
  }
  std::ifstream file(argv[2]);
  if (!file.is_open())
  {
    std::cerr << "file is not open\n";
    return 1;
  }

}

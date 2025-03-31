#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include "calculate_arithmetic_expressions.hpp"

namespace
{
  int checkArguments(const int argc);

  int checkArguments(const int argc)
  {
    if (argc == 2)
    {
      return 1;
    }
    else if (argc == 1)
    {
      return 2;
    }
    else 
    {
      return 0;
    }
  }
}

int main(int argc, const char * const * argv)
{
  std::string text;
  std::queue< std::string > queue;
  if (!checkArguments(argc))
  {
    std::cerr << "ERROR: Too many arguments";
    std::cerr << "\n";
    return 1;
  }
  else if (checkArguments(argc) == 1)
  {
    std::ifstream input(argv[1]);
    while (input)
    {
      input >> text;
      if (input.eof())
      {
        break;
      }
      else
      {
        queue.push(text);
      }
    }
  }
  else if (checkArguments(argc) == 2)
  {
    while (std::cin)
    {
      std::cin >> text;
      if (std::cin.eof())
      {
        break;
      }
      else
      {
        queue.push(text);
      }
    }
  }
  int * results = petrov::calculateArithmeticExpressions(queue);
  std::cout << results[0] << "\n";
}
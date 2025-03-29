#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include "calculate_arithmetic_expression.hpp"

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
      std::cerr << "Too many arguments\n";
      return 0;
    }
  }
}

int main(int argc, const char * const * argv)
{
  std::queue< std::string > queue;
  std::stack< std::string > stack;
  std::string text;
  if (checkArguments(argc) == 1)
  {
    std::ifstream input(argv[2]);
    while (!std::cin.eof())
    {
      input >> text;
      if (text == "\n")
      {
        std::queue< std::string > new_queue = petrov::transformInfixToPostfix(queue);
        std::cout << petrov::calculatePostfixExpression(new_queue);
        std::cout << "\n";
        continue;
      }
      queue.push(text);
    }
  }
  else if (checkArguments(argc) == 2)
  {
    while (!std::cin.eof())
    {
      std::cin >> text;
      if (text == "\n")
      {
        std::queue< std::string > new_queue = petrov::transformInfixToPostfix(queue);
        std::cout << petrov::calculatePostfixExpression(new_queue);
        std::cout << "\n";
        continue;
      }
      queue.push(text);
    }
  }
}
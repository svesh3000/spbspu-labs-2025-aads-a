#include <iostream>
#include <fstream>
#include "postfix-expression.h"

int main(int argc, char ** argv)
{
  if (argc > 2)
  {
    std::cerr << "ERROR: Too many arguments\n";
    return 1;
  }

  std::string text;
  std::ifstream in;

  if (argc == 2)
  {
    in.open(argv[1]);
    std::getline(in, text);
  }
  else
  {
    std::getline(std::cin, text);
  }

  savintsev::PostfixExpr expr;

  try
  {
    expr = text;
  }
  catch (const std::exception & e)
  {
    std::cerr << "lox" << '\n';
    return 1;
  }
  std::cout << expr.get_result() << '\n';
}

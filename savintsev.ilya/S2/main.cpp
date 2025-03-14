#include <iostream>
#include <stack>
#include <queue>
#include "postfix-expression.h"

int main()
{
  std::string text;
  std::getline(std::cin, text);

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

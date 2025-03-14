#include <iostream>
#include <stack>
#include <queue>
#include "postfix-expression.h"

int main()
{
  std::string text;
  std::getline(std::cin, text);

  try
  {
    savintsev::PostfixExpr expr(text);
    std::cout << expr.get_result() << '\n';
  }
  catch (const std::exception & e)
  {
    std::cerr << "lox" << '\n';
  }
}

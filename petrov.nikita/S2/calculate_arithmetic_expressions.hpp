#ifndef CALCULATE_ARITHMETIC_EXPRESSIONS_HPP
#define CALCULATE_ARITHMETIC_EXPRESSIONS_HPP

#include <string>
#include <queue>
#include <stack>

namespace petrov
{
  int * calculateArithmeticExpressions(std::queue< std::string > & queue);
  std::queue< std::string > transformInfixToPostfix(std::queue< std::string > & queue);
  std::stack< int > calculatePostfixExpression(std::queue< std::string > & queue);
}

#endif
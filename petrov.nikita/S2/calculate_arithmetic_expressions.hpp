#ifndef CALCULATE_ARITHMETIC_EXPRESSIONS_HPP
#define CALCULATE_ARITHMETIC_EXPRESSIONS_HPP

#include <string>
#include <queue>
#include <stack>

namespace petrov
{
  std::stack< int > calculateArithmeticExpressions(std::queue< std::string > & queue);
  std::queue< std::string > transformInfixToPostfix(std::queue< std::string > & queue);
  int calculatePostfixExpression(std::queue< std::string > & queue);
}

#endif
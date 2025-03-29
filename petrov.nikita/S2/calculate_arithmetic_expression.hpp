#ifndef CALCULATE_ARITHMETIC_EXPRESSION_HPP
#define CALCULATE_ARITHMETIC_EXPRESSION_HPP

#include <queue>
#include <string>

namespace petrov
{
  std::queue< std::string > & transformInfixToPostfix(std::queue< std::string > & queue);
  int calculatePostfixExpression(std::queue< std::string > & queue);
}

#endif
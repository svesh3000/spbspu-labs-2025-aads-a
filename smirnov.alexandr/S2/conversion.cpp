#include "conversion.hpp"
#include <sstream>
#include <cmath>
#include "utils.hpp"

smirnov::Queue< std::string > smirnov::infixToPostfix(const std::string & infix)
{
  Queue< std::string > output;
  Stack< std::string > opStack;
  std::istringstream iss(infix);
  std::string token;
  while (iss >> token)
  {
    if (token == "(")
    {
      opStack.push(token);
    }
    else if (token == ")")
    {
      while (!opStack.empty() && opStack.top() != "(")
      {
        output.push(opStack.drop());
      }
      opStack.drop();
    }
    else if (isOperator(token))
    {
      while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(token))
      {
        output.push(opStack.drop());
      }
      opStack.push(token);
    }
    else
    {
      output.push(token);
    }
  }
  while (!opStack.empty())
  {
    output.push(opStack.drop());
  }
  return output;
}

double smirnov::evaluatePostfix(Queue< std::string > & postfix)
{
  Stack< double > values;
  while (!postfix.empty())
  {
    std::string token = postfix.front();
    postfix.drop();
    if (isOperator(token))
    {
      double b = values.drop();
      double a = values.drop();
      if (token == "+")
      {
        values.push(a + b);
      }
      else if (token == "-")
      {
        values.push(a - b);
      }
      else if (token == "*")
      {
        values.push(a * b);
      }
      else if (token == "/")
      {
        values.push(a / b);
      }
      else if (token == "%")
      {
        values.push(std::fmod(a, b));
      }
    }
    else
    {
      values.push(std::stod(token));
    }
  }
  return values.drop();
}

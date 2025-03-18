#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

#include "queue.hpp"
#include "stack.hpp"
#include "variant.hpp"

namespace rychkov
{
  int executeOperation(int leftOperand, char operation, int rightOperand)
  {
    switch (operation)
    {
    case '*':
      return leftOperand * rightOperand;
    case '/':
      return leftOperand / rightOperand;
    case '+':
      return leftOperand + rightOperand;
    case '-':
      return leftOperand - rightOperand;
    case '%':
      return leftOperand % rightOperand;
    }
    return 0;
  }
  int getPriority(char operatorChar)
  {
    switch (operatorChar)
    {
    case '(':
    case ')':
      return 1;
    case '%':
      return 2;
    case '+':
    case '-':
      return 3;
    case '*':
    case '/':
      return 4;
    default:
      return -1;
    }
  }
  char pushLowPrioritized(rychkov::Queue< rychkov::Variant< int, char > >& expression,
      rychkov::Stack< char >& operators, int referencePriority = 0)
  {
    while (!operators.empty() && (rychkov::getPriority(operators.top()) > referencePriority))
    {
      expression.push(operators.top());
      operators.pop();
    }
    char result = '\0';
    if (!operators.empty() && (rychkov::getPriority(operators.top()) == referencePriority))
    {
      result = operators.top();
      if (operators.top() != '(')
      {
        expression.push(operators.top());
      }
      operators.pop();
    }
    return result;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "console arguments count doesn't match requirenment\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "failed to open file \"" << argv[1] << "\"\n";
    return 1;
  }
  in >> std::noskipws;
  rychkov::Queue< rychkov::Variant< int, char > > expression;
  rychkov::Stack< char > operators;
  bool isNumber = false;
  int number = 0;
  char c = 0;
  while (in >> c)
  {
    if (std::isdigit(c))
    {
      isNumber = true;
      number = number * 10 + (c - '0');
    }
    else
    {
      if (isNumber)
      {
        expression.push(number);
      }
      isNumber = false;
      number = 0;
      if (!std::isspace(c))
      {
        int priority = rychkov::getPriority(c);
        if (priority == -1)
        {
          std::cerr << "found unknown symbol - '" << c << "'\n";
          return 1;
        }
        if (c == '(')
        {
          operators.push(c);
          continue;
        }
        char equalPrioritized = rychkov::pushLowPrioritized(expression, operators, priority);
        if ((equalPrioritized != '(') && (c == ')'))
        {
          std::cerr << "wrong parentheses order\n";
          return 1;
        }
        if (c != ')')
        {
          operators.push(c);
        }
      }
    }
  }
  rychkov::pushLowPrioritized(expression, operators, 0);
  operators.clear();

  /*for (; !expression.empty(); expression.pop())
  {
    if (rychkov::holds_alternative< char >(expression.front()))
    {
      std::cout << rychkov::get< char >(expression.front());
    }
    else
    {
      std::cout << rychkov::get< int >(expression.front());
    }
  }
  return 0;*/

  rychkov::Stack< int > operands;
  if (expression.empty() || !rychkov::holds_alternative< int >(expression.front()))
  {
    std::cerr << "expression don't starts with number\n";
    return 1;
  }
  operands.push(rychkov::get< int >(expression.front()));
  expression.pop();
  for (; !expression.empty(); expression.pop())
  {
    if (rychkov::holds_alternative< char >(expression.front()))
    {
      if (operands.size() < 2)
      {
        std::cerr << "missing operand (number)\n";
        return 1;
      }
      int rightOperand = operands.top();
      operands.pop();
      operands.top() = rychkov::executeOperation(operands.top(), rychkov::get< char >(expression.front()), rightOperand);
    }
    else
    {
      operands.push(rychkov::get< int >(expression.front()));
    }
  }
  if (operands.size() != 1)
  {
    std::cerr << "missing operator\n";
    return 1;
  }
  std::cout << operands.top() << '\n';
}

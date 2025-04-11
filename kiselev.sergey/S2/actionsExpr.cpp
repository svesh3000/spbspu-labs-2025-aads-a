#include "actionsExpr.hpp"
#include <limits>
#include <cctype>
#include <new>
#include <ostream>
#include <stdexcept>
#include <string>

namespace
{
  int getPriority(const char& operation)
  {
    if (operation == '+' || operation == '-')
    {
      return 1;
    }
    else if (operation == '*' || operation == '/' || operation == '%')
    {
      return 2;
    }
    return 0;
  }

  bool isOperator(const char& c)
  {
    return c == '+' || c == '-' || c == '/' || c == '*' || c == '%';
  }
  void addNumberInLine(std::string& line, std::string& number)
  {
    if (!number.empty())
    {
      if (!line.empty())
      {
        line += ' ';
      }
      line += number;
      number.clear();
    }
  }

  void addNumberInStack(std::string& number, kiselev::stackNumber& stack)
  {
    if (!number.empty())
    {
      stack.push(std::stoll(number));
      number.clear();
    }
  }

  void checkMultiplicate(long long int a, long long int b)
  {
    long long int max = std::numeric_limits< long long int >::max();
    long long int min = std::numeric_limits< long long int >::min();
    bool isOverflow = false;
    if (a > 0 && b > 0 && a > max / b)
    {
      isOverflow = true;
    }
    else if (a > 0 && b < 0 && b < min / a)
    {
      isOverflow = true;
    }
    else if (a < 0 && b > 0 && a < min / b)
    {
      isOverflow = true;
    }
    else if (a < 0 && b < 0 && b < max / a)
    {
      isOverflow = true;
    }
    if (isOverflow)
    {
      throw std::logic_error("Overflow");
    }
  }
  void checkSum(long long int a, long long int b)
  {
    long long int max = std::numeric_limits< long long int >::max();
    if (a > max - b)
    {
      throw std::logic_error("Overflow");
    }
  }
  void checkDifference(long long int a, long long b)
  {
    long long int min = std::numeric_limits< long long int >::min();
    if (a < min + b)
    {
      throw std::logic_error("Underflow");
    }
  }
  void checkDivision(long long int b)
  {
    if (b == 0)
    {
      throw std::logic_error("Dividing by 0");
    }
  }
  long long int calculatingOperation(long long int a, long long b, const char& operation)
  {
    switch (operation)
    {
    case '+':
      checkSum(a, b);
      return a + b;
    case '-':
      checkDifference(a, b);
      return a - b;
    case '*':
      checkMultiplicate(a, b);
      return a * b;
    case '/':
      checkDivision(b);
      return a / b;
    case '%':
      checkDivision(b);
      return a >= 0 ? a % b : (b - std::abs(a % b)) % b;
    default:
      throw std::logic_error("Invalid operation");
    }
  }

}

kiselev::queue kiselev::convertExpr(queue& infix)
{
  queue postfix;
  Stack< char > operators;
  std::string number;
  while (!infix.empty())
  {
    std::string line = infix.front();
    infix.pop();
    std::string postfixLine;
    for (char s: line)
    {
      if (std::isspace(s))
      {
        addNumberInLine(postfixLine, number);
        continue;
      }
      if (std::isdigit(s))
      {
        number += s;
      }
      else
      {
        addNumberInLine(postfixLine, number);
        if (s == '(')
        {
          operators.push(s);
        }
        else if (isOperator(s))
        {
          while (!operators.empty() && getPriority(operators.top()) >= getPriority(s))
          {
            postfixLine += ' ';
            postfixLine += operators.top();
            operators.pop();
          }
          operators.push(s);
        }
        else if (s == ')')
        {
          while (!operators.empty() && operators.top() != '(')
          {
            postfixLine += ' ';
            postfixLine += operators.top();
            operators.pop();
          }
          operators.pop();
        }
      }
    }
    addNumberInLine(postfixLine, number);
    while (!operators.empty())
    {
      postfixLine += ' ';
      postfixLine += operators.top();
      operators.pop();
    }
    postfix.push(postfixLine);
  }
  return postfix;
}

kiselev::stackNumber kiselev::calculationExpr(queue& postfix)
{
  stackNumber results;
  while (!postfix.empty())
  {
    stackNumber numbers;
    std::string line = postfix.front();
    postfix.pop();
    std::string number;
    for (char s: line)
    {
      if (std::isspace(s))
      {
        addNumberInStack(number, numbers);
        continue;
      }
      if (std::isdigit(s))
      {
        number += s;
      }
      else if (isOperator(s))
      {
        addNumberInStack(number, numbers);
        if (numbers.size() < 2)
        {
          throw std::logic_error("Not enough operands");
        }
        long long int right = numbers.top();
        numbers.pop();
        long long int left = numbers.top();
        numbers.pop();
        long long int result = calculatingOperation(left, right, s);
        numbers.push(result);
      }
    }
    addNumberInStack(number, numbers);
    if (numbers.size() != 1)
    {
      throw std::logic_error("Too many operands");
    }
    results.push(numbers.top());
  }

  return results;
}

void kiselev::inputExprs(std::istream& input, queue& exprs)
{
  std::string line;
  while (std::getline(input, line))
  {
    if (line.empty())
    {
      continue;
    }
    exprs.push(line);
  }
}

std::ostream& kiselev::outputResults(std::ostream& output, stackNumber& results)
{
  if (!results.empty())
  {
    output << results.top();
    results.pop();
    while (!results.empty())
    {
      output << " " << results.top();
      results.pop();
    }
  }
  return output;
}

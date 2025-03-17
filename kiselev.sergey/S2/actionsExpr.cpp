#include "actionsExpr.hpp"
#include <limits>
#include <cctype>
#include <string>

namespace
{
  int getPriority(const char& operation)
  {
    if (operation == '+' || '-')
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
  void addNumber(std::string& line, std::string& number)
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

  bool isOverflow(long long int a, long long int b)
  {
    long long int max = std::numeric_limits< long long int >::max();
    long long int min = std::numeric_limits< long long int >::min();
    if (a > 0 && b > 0 && a > max / b)
    {
      return true;
    }
    else if (a > 0 && b < 0 && b < min / a)
    {
      return true;
    }
    else if (a < 0 && b > 0 && a < min / b)
    {
      return true;
    }
    else if (a < 0 && b < 0 && b < max / a)
    {
      return true;
    }
    return false;
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
    for (char s : line)
    {
      if (isspace(s))
      {
        addNumber(postfixLine, number);
        continue;
      }
      if (isdigit(s))
      {
        number += s;
      }
      else
      {
        addNumber(postfixLine, number);
        if (s == '(')
        {
          operators.push(s);
        }
        else if (isOperator(s))
        {
          while (!operators.empty() && getPriority(operators.back()) >= getPriority(s))
          {
            postfixLine += ' ';
            postfixLine += operators.back();
            operators.pop();
          }
          operators.push(s);
        }
        else if (s == ')')
        {
          while (!operators.empty() && operators.back() != '(')
          {
            postfixLine += ' ';
            postfixLine += operators.back();
            operators.pop();
          }
          operators.pop();
        }
      }
    }
    addNumber(postfixLine, number);
    while (!operators.empty())
    {
      postfixLine += ' ';
      postfixLine += operators.back();
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
    for (size_t i = 0; i < line.size(); ++i)
    {
      char s = line[i];
      if (std::isspace(s))
      {
        continue;
      }
      if (std::isdigit(s))
      {
        std::string number;
        while (i < line.size() && std::isdigit(s))
        {
          number += line[i];
          ++i;
        }
        --i;
        result.push(std::stoll(number));
      }
      else if (isOperator(s))
      {
      }
    }
  }
}

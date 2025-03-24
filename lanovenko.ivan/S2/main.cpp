#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <queue>
#include <stack>

std::string parseDigit(const std::string& str, size_t& num)
{
  std::string result = "";
  for (size_t i = num; i < str.length(); i++)
  {
    if (str[num] == ' ')
    {
      break;
    }
    else
    {
      result += str[i];
      num++;
    }
  }
  return result;
}

size_t getPriority(char c)
{
  size_t result = 0;
  if (c == '(')
  {
    result = 0;
  }
  if (c == ')')
  {
    result = 1;
  }
  if (c == '+' || c == '-')
  {
    result = 2;
  }
  if (c == '*' || c == '/' || c == '%')
  {
    result = 3;
  }
  return result;
}

void pushSign(std::queue< std::string >& result, std::stack< char >& operations, char sign)
{
  if (operations.empty())
  {
    operations.push(sign);
  }
  else if (!operations.empty())
  {
    while (!operations.empty() && getPriority(sign) <= getPriority(operations.top()))
    {
      result.push(operations.top() + std::string{ " " });
      operations.pop();
    }
    operations.push(sign);
  }
}

bool additionOverflow(long long a, long long b)
{
  return (b > std::numeric_limits<long long>::max() - a);
}

bool multiplicationOverflow(long long a, long long b)
{
  if (a == 0 || b == 0)
  {
    return false;
  }
  if (a > 0)
  {
    if (b > 0)
    {
      return a > std::numeric_limits< long long >::max() / b;
    }
    else
    {
      return b < std::numeric_limits<long long >::min() / a;
    }
  }
  else
  {
    if (b > 0)
    {
      return a < std::numeric_limits< long long >::min() / b;
    }
    else
    {
      return a < std::numeric_limits< long long >::max() / b;
    }
  }
}

long long calculateBinary(long long a, long long b, char operation)
{
  if (operation == '+')
  {
    if (additionOverflow(a, b))
    {
      throw std::logic_error("Sum overflow");
    }
    return a + b;
  }
  if (operation == '-')
  {
    return a - b;
  }
  if (operation == '*')
  {
    if (multiplicationOverflow(a, b))
    {
      throw std::logic_error("Multiplication overflow");
    }
    return a * b;
  }
  if (operation == '/')
  {
    if (b == 0)
    {
      throw std::invalid_argument("Division by zero!");
    }
    return (a / b);
  }
  if (operation == '%')
  {
    if (b == 0)
    {
      throw std::invalid_argument("Division by zero!");
    }
    return ((a % b) + b) % b;
  }
  return 0;
}

void pushCalculated(std::stack < long long >& result, char operation)
{
  if (result.empty())
  {
    throw std::invalid_argument("Wrong expression");
  }
  long long b = result.top();
  result.pop();
  if (result.empty())
  {
    throw std::invalid_argument("Wrong eptession");
  }
  long long a = result.top();
  result.pop();
  result.push(calculateBinary(a, b, operation));
}

std::queue<std::string> toPostfix(const std::string& infix)
{
  std::queue < std::string > result;
  std::stack< char > operations{};
  for (size_t i = 0; i < infix.size(); i++)
  {
    if (std::isdigit(infix[i]))
    {
      result.push(parseDigit(infix, i) + " ");
    }
    if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%')
    {
      pushSign(result, operations, infix[i]);
    }
    if (infix[i] == '(')
    {
      operations.push(infix[i]);
    }
    if (infix[i] == ')')
    {
      while (!operations.empty() && operations.top() != '(')
      {
        result.push(operations.top() + std::string{ " " });
        operations.pop();
      }
      if (!operations.empty())
      {
        operations.pop();
      }
      else
      {
        throw std::invalid_argument("incorrectly placed brackets!");
      }
    }
  }
  while (!operations.empty())
  {
    if (operations.top() == '(')
    {
      throw std::invalid_argument("incorrectly placed brackets!");
    }
    result.push(operations.top() + std::string{ " " });
    operations.pop();
  }
  if (result.empty())
  {
    throw std::invalid_argument("nothing to transorm");
  }
  return result;
}

long long calcualtePostfix(std::queue< std::string >& postfix)
{
  std::stack < long long > result;
  while (!postfix.empty())
  {
    char current = postfix.front().front();
    if (std::isdigit(current))
    {
      result.push(std::stoll(postfix.front()));
    }
    if (current == '+' || current == '-' || current == '*' || current == '/' || current == '%')
    {
      pushCalculated(result, current);
    }
    postfix.pop();
  }
  long long res = result.top();
  result.pop();
  return res;
}

void resultsOutput(std::stack < long long > results, std::ostream& out)
{
  if (!results.empty())
  {
    out << results.top();
    results.pop();
  }
  while (!results.empty())
  {
    out << " " << results.top();
    results.pop();
  }
}

void inputExpression(std::istream& in, std::queue < std::string >& infixExpressions)
{
  while (!in.eof())
  {
    std::string expression = "";
    std::getline(in, expression, '\n');
    if (!expression.empty())
    {
      infixExpressions.push(expression);
    }
  }
}

int main(int argc, char** argv)
{
  if (argc > 2)
  {
    std::cerr << "to much parametrs!\n";
    return 1;
  }
  std::queue < std::string > infixExpressions{};
  if (argc == 1)
  {
    inputExpression(std::cin, infixExpressions);
  }
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    inputExpression(input, infixExpressions);
  }
  std::queue< std::queue < std::string > > postfixExpressions;
  while (!infixExpressions.empty())
  {
    std::string expression = infixExpressions.front();
    try
    {
      postfixExpressions.push(toPostfix(expression));
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what();
      return 1;
    }
    infixExpressions.pop();
  }
  std::stack < long long > results{};
  while (!postfixExpressions.empty())
  {
    long long res = 0;
    try
    {
      res = calcualtePostfix(postfixExpressions.front());
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what();
      return 1;
    }
    catch (const std::logic_error& e)
    {
      std::cerr << e.what();
      return 1;
    }
    results.push(res);
    postfixExpressions.pop();
  }
  resultsOutput(results, std::cout);
}

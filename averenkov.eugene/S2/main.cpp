#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "stack.hpp"
#include "queue.hpp"


using namespace averenkov;

bool isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int precedence(char op)
{
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/' || op == '%') return 2;
  return 0;
}


std::string infixToPostfix(const std::string& infix)
{
  Stack< char > stack;
  Queue< char > queue;
  std::string number;

  for (char ch : infix)
  {
    if (std::isspace(ch)) continue;

    if (std::isdigit(ch))
    {
      number += ch;
    }
    else
    {
      if (!number.empty())
      {
        for (char digit : number)
        {
          queue.push(digit);
        }
        queue.push(' ');
        number.clear();
      }

      if (ch == '(')
      {
        stack.push(ch);
      }
      else if (ch == ')')
      {
        while (!stack.empty() && stack.top() != '(')
        {
          queue.push(stack.drop());
        }
        if (stack.empty())
        {
          throw std::runtime_error("parentheses error");
        }
        stack.drop();
      }
      else if (isOperator(ch))
      {
        while (!stack.empty() && precedence(stack.top()) >= precedence(ch))
        {
          queue.push(stack.drop());
        }
        stack.push(ch);
      }
      else
      {
        throw std::runtime_error("error character in expression");
      }
    }
  }

  if (!number.empty())
  {
    for (char digit : number)
    {
      queue.push(digit);
    }
    queue.push(' ');
  }

  while (!stack.empty())
  {
    if (stack.top() == '(')
    {
      throw std::runtime_error("parentheses error");
    }
    queue.push(stack.drop());
  }

  std::string postfix;
  while (!queue.empty())
  {
    postfix += queue.drop();
  }

  return postfix;
}

int evaluatePostfix(const std::string& postfix)
{
  Stack< int > stack;
  std::istringstream iss(postfix);
  std::string token;

  while (iss >> token)
  {
    if (std::isdigit(token[0]))
    {
      stack.push(std::stoi(token));
    }
    else if (isOperator(token[0]))
    {
      if (stack.size() < 2)
      {
        throw std::runtime_error("expression error");
      }
      int b = stack.drop();
      int a = stack.drop();
      switch (token[0])
      {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/':
          if (b == 0)
          {
            throw std::runtime_error("division zero");
          }
          stack.push(a / b);
          break;
        case '%':
          if (b == 0)
          {
            throw std::runtime_error("modul zero");
          }
          stack.push(a % b);
          break;
        default:
          throw std::runtime_error("invalid operator");
      }
    }
    else
    {
      throw std::runtime_error("invalid token");
    }
  }

  return stack.drop();
}

void processExpressions(std::istream& input)
{
  Stack< int > results;
  std::string line;
  std::string token;

  while (input >> token)
  {
    if (token == "(" || token == ")" || isOperator(token[0]) || std::isdigit(token[0]))
    {
      line += token + " ";
    }
    else
    {
      throw std::runtime_error("invalid token");
    }

    if (input.peek() == '\n' || input.peek() == EOF)
    {
      if (!line.empty())
      {
        try
        {
          std::string postfix = infixToPostfix(line);
          int result = evaluatePostfix(postfix);
          results.push(result);
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << "\n";
          return;
        }
        line.clear();
      }
    }
  }

  while (!results.empty())
  {
    std::cout << results.drop() << " ";
  }
  std::cout << "\n";
}

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Error\n";
    return 1;
  }

  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    if (!file)
    {
      std::cerr << "Error\n";
      return 1;
    }
    processExpressions(file);
  }
  else
  {
    processExpressions(std::cin);
  }

  return 0;
}

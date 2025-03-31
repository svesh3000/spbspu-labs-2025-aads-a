#include "calculate_arithmetic_expressions.hpp"
#include <iostream>

namespace
{
  int isdigit(std::string & string);

  int isdigit(std::string & string)
  {
    return string.find_first_not_of("0123456789") == string.npos;
  }
}

int * petrov::calculateArithmeticExpressions(std::queue< std::string > & queue)
{
  std::queue< std::string > new_queue = transformInfixToPostfix(queue);
  std::stack< int > stack = calculatePostfixExpression(new_queue);
  int * results = new int[stack.size()];
  for (size_t i = 0; i < stack.size(); i++)
  {
    results[i] = stack.top();
    stack.pop();
  }
  return results;
}

std::queue< std::string > petrov::transformInfixToPostfix(std::queue< std::string > & queue)
{
  std::stack< std::string > stack;
  std::queue< std::string > new_queue;
  while (!queue.empty())
  {
    std::cout << "Queue members:\n";
    std::string token = queue.front();
    std::cout << token << "\n";
    if (isdigit(token))
    {
      new_queue.push(token);
    }
    else if (token == "(")
    {
      stack.push(token);
    }
    else if (token == ")")
    {
      while (stack.top() != "(")
      {
        new_queue.push(stack.top());
        stack.pop();
      }
      stack.pop();
    }
    else if (token == "*" || token == "/" || token == "%")
    {
      if (stack.empty() || stack.top() == "/" || stack.top() == "*" || stack.top() == "%")
      {
        if (stack.empty())
        {
          stack.push(token);
        }
        else
        {
          while (!stack.empty() || stack.top() != "(")
          {
            new_queue.push(stack.top());
            stack.pop();
            stack.push(token);
          }
        }
      }
      else
      {
        stack.push(token);
      }
    }
    else if (token == "+" || token == "-")
    {
      if (stack.empty() ||  stack.top() == "/" || stack.top() == "*" || stack.top() == "%" || stack.top() == "+" || stack.top() == "-")
      {
        if (stack.empty())
        {
          stack.push(token);
        }
        else
        {
          while (!stack.empty() || stack.top() != "(")
          {
            new_queue.push(stack.top());
            stack.pop();
            stack.push(token);
          }
        }
      }
      else
      {
        stack.push(token);
      }
    }
    queue.pop();
  }
  while (!stack.empty())
  {
    new_queue.push(stack.top());
    stack.pop();
  }
  return new_queue;
}

std::stack< int > petrov::calculatePostfixExpression(std::queue< std::string > & queue)
{
  std::stack< int > stack;
  int result = 0;
  while (!queue.empty())
  {
    std::cout << "New queue members:\n";
    std::string token = queue.front();
    std::cout << token << "\n";
    if (isdigit(token))
    {
      stack.push(std::stoi(token));
    }
    else if (token == "*")
    {
      int first_operand = stack.top();
      stack.pop();
      int second_operand = stack.top();
      stack.pop();
      result = second_operand * first_operand;
      stack.push(result);
    }
    else if (token == "/")
    {
      int first_operand = stack.top();
      stack.pop();
      int second_operand = stack.top();
      stack.pop();
      result = second_operand / first_operand;
      stack.push(result);
    }
    else if (token == "%")
    {
      int first_operand = stack.top();
      stack.pop();
      int second_operand = stack.top();
      stack.pop();
      result = second_operand % first_operand;
      stack.push(result);
    }
    else if (token == "+")
    {
      int first_operand = stack.top();
      stack.pop();
      int second_operand = stack.top();
      stack.pop();
      result = second_operand + first_operand;
      stack.push(result);
    }
    else if (token == "-")
    {
      int first_operand = stack.top();
      stack.pop();
      int second_operand = stack.top();
      stack.pop();
      result = second_operand - first_operand;
      stack.push(result);
    }
    queue.pop();
  }
  return stack;
}

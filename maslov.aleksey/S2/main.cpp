#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "stack.hpp"

bool isNumber(const std::string & element)
{
  try
  {
    std::stoi(element);
  }
  catch (const std::exception &)
  {
    return false;
  }
  return true;
}

bool isOperator(const std::string & el)
{
  return (el == "+" || el == "-" || el == "*" || el == "/" || el == "%");
}

int getPrecedence(const std::string & op)
{
  if (op == "+" || op == "-")
  {
    return 1;
  }
  if (op == "*" || op == "/" || op == "%")
  {
    return 2;
  }
  return 0;
}

long long int calculateOperation(long long int op1, long long int op2, const std::string & el)
{
  if (el == "+")
  {
    return op1 + op2;
  }
  else if (el == "-")
  {
    return op1 - op2;
  }
  else if (el == "*")
  {
    return op1 * op2;
  }
  else if (el == "/")
  {
    if (op2 == 0)
    {
      throw std::runtime_error("ERROR: division by zero");
    }
    return op1 / op2;
  }
  else if (el == "%")
  {
    if (op2 == 0)
    {
      throw std::runtime_error("ERROR: division by zero");
    }
    return op1 % op2;
  }
  else
  {
    throw std::runtime_error("ERROR: invalid operator");
  }
}

long long int calculatePostfix(maslov::Queue< std::string > postfixQueue)
{
  maslov::Stack< long long int > stack;
   while (!postfixQueue.empty())
   {
    std::string element = postfixQueue.front();
    postfixQueue.pop();
    if (isNumber(element))
    {
      stack.push(std::stoll(element));
    }
    else if (isOperator(element))
    {
      if (stack.size() < 2)
      {
        throw std::runtime_error("ERROR: the operator requires at least 2 operands");
      }
      long long int operand2 = stack.top();
      stack.pop();
      long long int operand1 = stack.top();
      stack.pop();
      stack.push(calculateOperation(operand1, operand2, element));
    }
  }
  long long int result  = stack.top();
  stack.pop();
  return result;
}

maslov::Queue< std::string > infixToPostfix(maslov::Queue< std::string > infixQueue)
{
  maslov::Queue< std::string > postfixQueue;
  maslov::Stack< std::string > stack;
  while (!infixQueue.empty())
  {
    std::string element = infixQueue.front();
    if (element == "(")
    {
      stack.push(element);
    }
    else if (isNumber(element))
    {
      postfixQueue.push(element);
    }
    else if (element == ")")
    {
      while (!stack.empty() && stack.top() != "(")
      {
        postfixQueue.push(stack.top());
        stack.pop();
      }
      if (!stack.empty() && stack.top() == "(")
      {
        stack.pop();
      }
      else
      {
        throw std::runtime_error("ERROR: not found parentheses");
      }
    }
    else if (isOperator(element))
    {
      int elementPrecedence = getPrecedence(element);
      while (!stack.empty() && elementPrecedence <= getPrecedence(stack.top()))
      {
        postfixQueue.push(stack.top());
        stack.pop();
      }
      stack.push(element);
    }
    else
    {
      throw std::runtime_error("ERROR: invalid element");
    }
    infixQueue.pop();
  }
  return postfixQueue;
}

void splitExpression(const std::string & str, maslov::Queue< std::string > infixQueue)
{
  std::string element;
  char separator = ' ';
  for (size_t i = 0; i < str.length(); ++i)
  {
    if (str[i] != separator)
    {
      element += str[i];
    }
    else
    {
      if (!element.empty())
      {
        infixQueue.push(element);
        element.clear();
      }
    }
  }
  if (!element.empty())
  {
    infixQueue.push(element);
  }
}

void inputExpression(std::istream & in, maslov::Queue< maslov::Queue< std::string > > & queue)
{
  std::string str;
  while (std::getline(in, str))
  {
    if (str.empty())
    {
      continue;
    }
    maslov::Queue< std::string > infixQueue;
    splitExpression(str, infixQueue);
    queue.push(infixQueue);
  }
}

void inputFile(const std::string & filename, maslov::Queue< maslov::Queue< std::string > > & queue)
{
  if (!filename.empty())
  {
    std::ifstream fileInput(filename);
    if (!fileInput.is_open())
    {
      throw std::runtime_error("ERROR: cannot open the file");
    }
    inputExpression(fileInput, queue);
    fileInput.close();
  }
  else
  {
    inputExpression(std::cin, queue);
  }
}

int main(int argc, char ** argv)
{
  using namespace maslov;
  std::string filename;
  if (argc > 1)
  {
    filename = argv[1];
  }
  Queue< Queue< std::string > > queue;
  try
  {
    inputFile(filename, queue);
    while (!queue.empty())
    {
      Queue< std::string > infixQueue = queue.front();
      queue.pop();
      Queue< std::string > postfixQueue = infixToPostfix(infixQueue);
      double result = calculatePostfix(postfixQueue);
      std::cout << result << "\n";
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

#include "expr_convert.hpp"
#include <stdexcept>
#include <iostream>

namespace
{
  using lli = long long int;

  bool isNumber(const std::string& str)
  {
    try
    {
      std::stoll(str);
      return true;
    }
    catch(...)
    {
      return false;
    }
  }

  bool isOperator(const std::string& str)
  {
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "%";
  }

  lli  getOpPriority(const std::string& op)
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

  lli performOperation(lli op1, lli op2, const std::string& operation)
  {
    if (operation == "+")
    {
      return op1 + op2;
    }
    if (operation == "-")
    {
      return op1 - op2;
    }
    if (operation == "*")
    {
      return op1 * op2;
    }
    if (operation == "/")
    {
      if (op2 == 0)
      {
        throw std::logic_error("division by zero");
      }
      return op1 / op2;
    }
    if (operation == "%")
    {
      if (op2 == 0)
      {
        throw std::logic_error("zero modulation");
      }
      return op1 % op2;
    }
    throw std::logic_error("invalid operation");
  }
}

demehin::ExprQueue demehin::convertQueue(ExprQueue& infExpr)
{
  ExprQueue postExpr;
  Stack<std::string> stack;
  while (!infExpr.empty())
  {
    std::string front = infExpr.front();
    infExpr.pop();
    if (isNumber(front))
    {
      postExpr.push(front);
    }
    else if (front == "(")
    {
      stack.push(front);
    }
    else if (front == ")")
    {
      while (!stack.empty() && stack.top() != "(")
      {
        postExpr.push(stack.top());
        stack.pop();
      }
      if (stack.empty())
      {
        throw std::logic_error("wrong brackets");
      }
      stack.pop();
    }
    else if (isOperator(front))
    {
      while (!stack.empty() && getOpPriority(front) <= getOpPriority(stack.top()))
      {
        postExpr.push(stack.top());
        stack.pop();
      }
      stack.push(front);
    }
    else
    {
      throw std::logic_error("invalid argument");
    }
  }

  while (!stack.empty())
  {
    if (stack.top() == "(")
    {
      throw std::logic_error("wrong brackets");
    }
    postExpr.push(stack.top());
    stack.pop();
  }
  return postExpr;
}

void demehin::convertStack(ExprsStack& infStack, ExprsStack& postStack)
{
  while (!infStack.empty())
  {
    postStack.push(convertQueue(infStack.top()));
    infStack.pop();
  }
}

lli demehin::calculateExpr(const ExprQueue& expr)
{
  Stack< lli > stack;
  ExprQueue exprCpy(expr);
  while (!exprCpy.empty())
  {
    std::string token = exprCpy.front();
    exprCpy.pop();

    if (isNumber(token))
    {
      stack.push(std::stoll(token));
    }
    else
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("not enough operands");
      }
      lli op1 = stack.top();
      stack.pop();
      lli op2 = stack.top();
      stack.pop();

      lli result = performOperation(op2, op1, token);
      stack.push(result);
    }
  }

  return stack.top();
}

void demehin::getExprsValues(ExprsStack postStack, Stack< lli >& values)
{
  while (!postStack.empty())
  {
    values.push(calculateExpr(postStack.top()));
    postStack.pop();
  }
}


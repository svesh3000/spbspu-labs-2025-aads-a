#include "exprs_manip.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <calc_utils.hpp>

namespace
{
  using long_t = long long int;

  bool isOperator(const std::string& str)
  {
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "%";
  }

  long_t getOpPriority(const std::string& op)
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

  //long_t modulate(long_t a, long_t b)
  //{
    //if (b < 0)
    //{
     // return -modulate(-a, -b);
    //}

    //long_t res = a % b;
    //if (res < 0)
    //{
      //res += b;
    //}
    //return res;
  //}

  /*bool isMultipOverflow(long_t a, long_t b)
  {
    long_t max = std::numeric_limits< long_t >::max();
    long_t min = std::numeric_limits< long_t >::min();
    if (a > 0 && b > 0 && a > max / b)
    {
      return true;
    }
    if (a < 0 && b < 0 && a < max / b)
    {
      return true;
    }
    if (a > 0 && b < 0 && b < min / a)
    {
      return true;
    }
    if (a < 0 && b > 0 && a < min / b)
    {
      return true;
    }
    return false;
  }*/

  long_t performOperation(long_t op1, long_t op2, const std::string& operation)
  {
    //long_t max = std::numeric_limits< long_t >::max();
    //long_t min = std::numeric_limits< long_t >::min();
    if (operation == "+")
    {
      //if (op1 > max - op2)
      //{
        //throw std::logic_error("overflow");
      //}
      //return op1 + op2;
      return demehin::sumChecked(op1, op2);
    }
    if (operation == "-")
    {
      //if (op1 < min + op2 )
      //{
        //throw std::logic_error("underflow");
      //}
      //return op1 - op2;
      return demehin::subtractChecked(op1, op2);
    }
    if (operation == "*")
    {
      //if (isMultipOverflow(op1, op2))
      //{
        //throw std::logic_error("overflow");
      //}
      //return op1 * op2;
      return demehin::multipChecked(op1, op2);
    }
    if (operation == "/")
    {
      //if (op2 == 0)
      //{
        //throw std::logic_error("division by zero");
      //}
      //if ((op1 == min && op2 == -1) || (op2 == min && op1 == -1))
      //{
        //throw std::logic_error("overflow");
      //}
      //return op1 / op2;
      return demehin::divideChecked(op1, op2);
    }
    if (operation == "%")
    {
      //if (op2 == 0)
      //{
        //throw std::logic_error("zero modulation");
      //}
      //return modulate(op1, op2);
      return demehin::modulateChecked(op1, op2);
    }
    throw std::logic_error("invalid operation");
  }
}

demehin::ExprQueue demehin::convertQueue(ExprQueue& infExpr)
{
  ExprQueue postExpr;
  Stack< std::string > stack;
  while (!infExpr.empty())
  {
    std::string front = infExpr.front();
    infExpr.pop();
    try
    {
      std::stoll(front);
      postExpr.push(front);
    }
    catch (...)
    {
      if (front == "(")
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

long_t demehin::calculateExpr(const ExprQueue& expr)
{
  Stack< long_t > stack;
  ExprQueue exprCpy(expr);
  while (!exprCpy.empty())
  {
    std::string token = exprCpy.front();
    exprCpy.pop();

    try
    {
      stack.push(std::stoll(token));
    }
    catch (...)
    {
      if (stack.size() < 2)
      {
        throw std::logic_error("not enough operands");
      }
      long_t op1 = stack.top();
      stack.pop();
      long_t op2 = stack.top();
      stack.pop();

      long_t result = performOperation(op2, op1, token);
      stack.push(result);
    }
  }

  return stack.top();
}

void demehin::getExprsValues(ExprsStack postStack, Stack< long_t >& values)
{
  while (!postStack.empty())
  {
    values.push(calculateExpr(postStack.top()));
    postStack.pop();
  }
}


#include "postfix-expression.h"
#include <stdexcept>
#include <iostream>

void savintsev::PostfixExpr::operator=(std::string & infix_expr)
{
  using str = std::string;

  std::stack< str > stack;
  std::stack< int > calculations;

  size_t was_bracket = 0;

  size_t back = infix_expr.size() - 1;
  size_t begin = 0;
  size_t end = 0;

  while (end != back)
  {
    end = infix_expr.find(' ', begin);
    str token = infix_expr.substr(begin, end != str::npos ? end - begin : end = back);
    if (token == "")
    {
      begin = end + 1;
      continue;
    }
    else if (token == "(")
    {
      stack.push(token);
      was_bracket++;
    }
    else if (token == "+" || token == "-")
    {
      if (!stack.empty())
      {
        if (stack.top() != "(")
        {
          expr_.push(stack.top());
          calculate_result(stack.top(), calculations);
          stack.pop();
        }
      }
      stack.push(token);
    }
    else if (token == "*" || token == "/" || token == "%")
    {
      if (!stack.empty())
      {
        if (stack.top() == "*" || stack.top() == "*" || stack.top() == "%")
        {
          expr_.push(stack.top());
          calculate_result(stack.top(), calculations);
          stack.pop();
        }
      }
      stack.push(token);
    }
    else if (token == ")")
    {
      if (!was_bracket)
      {
        throw std::invalid_argument("ERROR: invalid expression");
      }
      while (stack.top() != "(")
      {
        expr_.push(stack.top());
        calculate_result(stack.top(), calculations);
        stack.pop();
      }
      stack.pop();
      --was_bracket;
    }
    else if (is_token_number(token))
    {
      calculations.push(std::stoi(token));
      expr_.push(token);
    }
    else
    {
      throw std::invalid_argument("ERROR: token unsupported");
    }
    begin = end + 1;
  }
  while (!stack.empty())
  {
    expr_.push(stack.top());
    calculate_result(stack.top(), calculations);
    stack.pop();
  }
  if (calculations.size() == 1)
  {
    result_ = calculations.top();
  }
  else
  {
    throw std::invalid_argument("ERROR: invalid expression");
  }
}

void savintsev::PostfixExpr::calculate_result(std::string token, std::stack< int > & calc) const
{
  if (calc.size() < 2)
  {
    throw std::invalid_argument("ERROR: invalid expression");
  }
  if (token == "+")
  {
    int r = calc.top();
    calc.pop();
    int l = calc.top();
    calc.pop();
    calc.push(l + r);
  }
  else if (token == "-")
  {
    int r = calc.top();
    calc.pop();
    int l = calc.top();
    calc.pop();
    calc.push(l - r);
  }
  else if (token == "*")
  {
    int r = calc.top();
    calc.pop();
    int l = calc.top();
    calc.pop();
    calc.push(l * r);
  }
  else if (token == "/")
  {
    int r = calc.top();
    calc.pop();
    int l = calc.top();
    calc.pop();
    calc.push(l / r);
  }
  else if (token == "%")
  {
    int r = calc.top();
    calc.pop();
    int l = calc.top();
    calc.pop();
    calc.push(l % r);
  }
}

bool savintsev::PostfixExpr::is_token_number(std::string token)
{
  for (size_t i = 0; i < token.size(); ++i)
  {
    if (!std::isdigit(token[i]))
    {
      return false;
    }
  }
  return true;
}

int savintsev::PostfixExpr::get_result() const
{
  return result_;
}

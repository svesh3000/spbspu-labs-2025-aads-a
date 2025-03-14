#include "postfix-expression.h"
#include <stdexcept>

savintsev::PostfixExpr::PostfixExpr(std::string infix_expr)
{
  infix_expr += " ";
  std::string token;
  size_t searching_pos = 0;
  size_t end_pos = 0;
  size_t was_bracket = 0;
  std::stack< std::string > stack;
  std::stack< int > calculations;
  while (end_pos != infix_expr.size() - 1)
  {
    end_pos = infix_expr.find(' ', searching_pos);
    token = infix_expr.substr(searching_pos, end_pos - searching_pos);
    if (token == " ")
    {
      searching_pos = end_pos + 1;
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
      throw std::invalid_argument("ERROR: invalid expression");
    }
    searching_pos = end_pos + 1;
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
    throw std::invalid_argument("ERROR: unsupported operand");
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

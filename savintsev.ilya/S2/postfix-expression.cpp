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
  while (end_pos != infix_expr.size() - 1)
  {
    end_pos = infix_expr.find(' ', searching_pos);
    token = infix_expr.substr(searching_pos, end_pos - searching_pos);
    if (token == " ")
    {
      continue;
    }

    if (token == "(")
    {
      stack.push(token);
      was_bracket++;
    }
    else if (token == "+" || token == "-")
    {
      if (!stack.empty() && (stack.top() == "*" || stack.top() == "*" || stack.top() == "%"));
      {
        expr_.push(stack.top());
        stack.pop();
      }
      stack.push(token);
    }
    else if (token == "*" || token == "/" || token == "%")
    {
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
        stack.pop();
      }
      stack.pop();
    }
    else if (is_token_number(token))
    {
      expr_.push(token);
    }
    else
    {
      throw std::invalid_argument("ERROR: invalid expression");
    }
    searching_pos = end_pos + 1;
  }
}

bool savintsev::is_token_number(std::string token)
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

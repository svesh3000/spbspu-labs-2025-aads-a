#include "postfix-expression.h"
#include <stdexcept>
#include <iostream>

namespace
{
  bool is_token_number(std::string token)
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
}

savintsev::PostfixExpr::PostfixExpr(const PostfixExpr & rhs):
  expr_(rhs.expr_)
{}

savintsev::PostfixExpr::PostfixExpr(PostfixExpr && rhs)
{
  std::swap(expr_, rhs.expr_);
}

savintsev::PostfixExpr savintsev::convert(const std::string & infix)
{
  PostfixExpr postfix;
  using str = std::string;

  std::stack< str > stack;

  size_t was_bracket = 0;

  size_t back = infix.size() - 1;
  size_t begin = 0;
  size_t end = 0;

  while (end != back)
  {
    end = infix.find(' ', begin);
    str token = infix.substr(begin, end != str::npos ? end - begin : end = back);
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
          postfix.expr_.push(stack.top());
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
          postfix.expr_.push(stack.top());
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
        postfix.expr_.push(stack.top());
        stack.pop();
      }
      stack.pop();
      --was_bracket;
    }
    else if (is_token_number(token))
    {
      postfix.expr_.push(token);
    }
    else
    {
      throw std::invalid_argument("ERROR: token unsupported");
    }
    begin = end + 1;
  }
  while (!stack.empty())
  {
    postfix.expr_.push(stack.top());
    stack.pop();
  }
  if (was_bracket)
  {
    throw std::invalid_argument("ERROR: invalid expression");
  }
  postfix.calculate_result(true);
  return postfix;
}

int savintsev::PostfixExpr::calculate_result(bool is_excepting) const
{
  std::queue< std::string > expr(expr_);
  std::stack< int > calc;

  while (expr.size())
  {
    std::string token = expr.front();
    expr.pop();
    if (is_token_number(token))
    {
      calc.push(std::stoi(token));
    }
    else
    {
      if (calc.size() < 2 && is_excepting)
      {
        throw std::invalid_argument("ERROR: invalid expression");
      }
      int r = calc.top();
      calc.pop();
      int l = calc.top();
      calc.pop();
      switch (*(token.data()))
      {
      case '+':
        calc.push(l + r);
        break;
      case '-':
        calc.push(l - r);
        break;
      case '*':
        calc.push(l * r);
        break;
      case '/':
        calc.push(l / r);
        break;
      case '%':
        calc.push(l % r);
        break;
      }
    }
  }
  if (calc.size() == 1)
  {
    return calc.top();
  }
  if (is_excepting)
  {
    throw std::invalid_argument("ERROR: invalid expression");
  }
  return 0;
}

int savintsev::PostfixExpr::operator()() const noexcept
{
  return calculate_result(false);
}

savintsev::PostfixExpr & savintsev::PostfixExpr::operator=(const PostfixExpr & rhs)
{
  if (std::addressof(rhs) != this)
  {
    expr_ = rhs.expr_;
  }
  return *this;
}

savintsev::PostfixExpr & savintsev::PostfixExpr::use_operator(const std::string & op, PostfixExpr rhs)
{
  while (rhs.expr_.size())
  {
    this->expr_.push(rhs.expr_.front());
    rhs.expr_.pop();
  }
  this->expr_.push(op);
  return *this;
}

savintsev::PostfixExpr savintsev::PostfixExpr::operator+(const PostfixExpr & rhs)
{
  PostfixExpr new_lhs(*this);
  return new_lhs.use_operator("+", rhs);
}

savintsev::PostfixExpr savintsev::PostfixExpr::operator-(const PostfixExpr & rhs)
{
  PostfixExpr new_lhs(*this);
  return new_lhs.use_operator("-", rhs);
}

savintsev::PostfixExpr savintsev::PostfixExpr::operator*(const PostfixExpr & rhs)
{
  PostfixExpr new_lhs(*this);
  return new_lhs.use_operator("*", rhs);
}

savintsev::PostfixExpr savintsev::PostfixExpr::operator/(const PostfixExpr & rhs)
{
  PostfixExpr new_lhs(*this);
  return new_lhs.use_operator("/", rhs);
}

savintsev::PostfixExpr savintsev::PostfixExpr::operator%(const PostfixExpr & rhs)
{
  PostfixExpr new_lhs(*this);
  return new_lhs.use_operator("%", rhs);
}

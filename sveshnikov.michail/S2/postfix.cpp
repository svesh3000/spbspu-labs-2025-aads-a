#include "postfix.hpp"
#include <limits>
#include <stdexcept>

namespace
{
  constexpr long long max_ll = std::numeric_limits< long long >::max();
  constexpr long long min_ll = std::numeric_limits< long long >::min();
  bool isOperator(std::string op);
  void isDivisionByZero(long long operand);
  size_t getPriority(std::string op);

  bool isOperator(std::string op)
  {
    return (op == "+" || op == "-" || op == "*" || op == "%" || op == "/");
  }

  void isDivisionByZero(long long operand)
  {
    if (operand == 0)
    {
      throw std::overflow_error("ERROR: Division by zero!");
    }
  }

  size_t getPriority(std::string op)
  {
    switch (op[0])
    {
    case '(':
      return 0;
    case ')':
      return 1;
    case '+':
    case '-':
      return 2;
    case '*':
    case '/':
    case '%':
      return 3;
    default:
      throw std::invalid_argument("ERROR: Unknown operator!");
    }
  }
}

sveshnikov::Postfix::Postfix(const Postfix &other):
  expr_(other.expr_)
{}

sveshnikov::Postfix::Postfix(Postfix &&other):
  expr_(std::move(other.expr_))
{}

sveshnikov::Postfix::Postfix(Queue< std::string > infix):
  expr_()
{
  Stack< std::string > stack;
  size_t num_open_paren = 0, num_close_paren = 0;
  size_t num_operators = 0, num_operands = 0;
  while (!infix.empty())
  {
    if (infix.front() == "(")
    {
      if (!stack.empty() && !isOperator(stack.top()) && stack.top() != "(")
      {
        throw std::logic_error("ERROR: Incorrect infix notation!");
      }
      stack.push("(");
      num_open_paren++;
    }
    else if (infix.front() == ")")
    {
      num_close_paren++;
      if (num_close_paren > num_open_paren || stack.top() == "(")
      {
        throw std::logic_error("ERROR: Incorrect infix notation!");
      }
      push_out_stack(stack, getPriority(infix.front()));
      stack.pop();
    }
    else if (isOperator(infix.front()))
    {
      if (num_operators > num_operands)
      {
        throw std::logic_error("ERROR: Incorrect infix notation!");
      }
      if (infix.front() == "+" || infix.front() == "-")
      {
        push_out_stack(stack, getPriority(infix.front()));
      }
      stack.push(infix.front());
    }
    else
    {
      num_operands++;
      if (num_operands > num_operators + 1)
      {
        throw std::logic_error("ERROR: Incorrect infix notation!");
      }
      stoll(infix.front());
      expr_.push(infix.front());
    }
    infix.pop();
  }
  if (num_close_paren != num_open_paren || num_operands != num_operators + 1)
  {
    throw std::logic_error("ERROR: Incorrect infix notation!");
  }
  push_out_stack(stack, 0);
}

void sveshnikov::Postfix::push_out_stack(Stack< std::string > &stack, size_t priority)
{
  while (!stack.empty() && priority <= getPriority(stack.top()))
  {
    expr_.push(stack.top());
    stack.pop();
  }
}

sveshnikov::Postfix &sveshnikov::Postfix::operator=(const Postfix &other)
{
  expr_ = other.expr_;
  return *this;
}

sveshnikov::Postfix &sveshnikov::Postfix::operator=(Postfix &&other) noexcept
{
  expr_ = std::move(other.expr_);
  return *this;
}

sveshnikov::Postfix sveshnikov::Postfix::operator+(const Postfix &other) const
{
  return arith_operator_impl(other, "+");
}

sveshnikov::Postfix sveshnikov::Postfix::operator-(const Postfix &other) const
{
  return arith_operator_impl(other, "-");
}

sveshnikov::Postfix sveshnikov::Postfix::operator/(const Postfix &other) const
{
  return arith_operator_impl(other, "/");
}

sveshnikov::Postfix sveshnikov::Postfix::operator%(const Postfix &other) const
{
  return arith_operator_impl(other, "%");
}

sveshnikov::Postfix sveshnikov::Postfix::operator*(const Postfix &other) const
{
  return arith_operator_impl(other, "*");
}

sveshnikov::Postfix sveshnikov::Postfix::arith_operator_impl(Postfix other, std::string op) const
{
  Postfix new_postfix(*this);
  for (size_t i = 0; i < other.expr_.getSize(); i++)
  {
    new_postfix.expr_.push(other.expr_.front());
    other.expr_.pop();
  }
  new_postfix.expr_.push(op);
  return new_postfix;
}

long long sveshnikov::Postfix::calculate() const
{
  Stack< long long > stack;
  Queue< std::string > queue(expr_);
  while (!queue.empty())
  {
    std::string curr = std::move(queue.front());
    queue.pop();
    if (isOperator(curr))
    {
      const long long op = stack.top();
      stack.pop();
      long long res = stack.top();
      stack.pop();
      if (curr == "+")
      {
        if (res > max_ll - op)
        {
          throw std::overflow_error("ERROR: Overflow when calculating the amount!");
        }
        res += op;
      }
      if (curr == "-")
      {
        if (res < min_ll + op)
        {
          throw std::underflow_error("ERROR: Underflow when calculating the difference!");
        }
        res -= op;
      }
      if (curr == "/")
      {
        isDivisionByZero(op);
        res /= op;
      }
      if (curr == "%")
      {
        isDivisionByZero(op);
        res %= op;
      }
      if (curr == "*")
      {
        if ((op == -1 && res == min_ll) || (op == min_ll && res == -1))
        {
          throw std::overflow_error("ERROR: Overflow when calculating the product!");
        }
        if (res != 0)
        {
          if ((op > 0 && res > max_ll / op) || (op < 0 && res < max_ll / op))
          {
            throw std::overflow_error("ERROR: Overflow when calculating the product!");
          }
          if ((op > 0 && res < min_ll / op) || (op < 0 && res > min_ll / op))
          {
            throw std::underflow_error("ERROR: Underflow when calculating the product!");
          }
        }
        res *= op;
      }
      stack.push(res);
    }
    else
    {
      stack.push(std::stoll(curr));
    }
  }
  return stack.top();
}

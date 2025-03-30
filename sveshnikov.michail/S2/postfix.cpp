#include "postfix.hpp"
#include <limits>
#include <stdexcept>
#include "stack.hpp"

namespace
{
  void isDivisionByZero(long long operand);

  void isDivisionByZero(long long operand)
  {
    if (operand == 0)
    {
      throw std::overflow_error("ERROR: Division by zero!");
    }
  }
}

sveshnikov::Postfix::Postfix(const Postfix &other):
  expr_(other.expr_)
{}

sveshnikov::Postfix::Postfix(Postfix &&other):
  expr_(std::move(other.expr_))
{}


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

sveshnikov::Postfix &sveshnikov::Postfix::operator+(const Postfix &other) const
{
  return arith_operator_impl(other, "+");
}

sveshnikov::Postfix &sveshnikov::Postfix::operator-(const Postfix &other) const
{
  return arith_operator_impl(other, "-");
}

sveshnikov::Postfix &sveshnikov::Postfix::operator/(const Postfix &other) const
{
  return arith_operator_impl(other, "/");
}

sveshnikov::Postfix &sveshnikov::Postfix::operator%(const Postfix &other) const
{
  return arith_operator_impl(other, "%");
}

sveshnikov::Postfix &sveshnikov::Postfix::operator*(const Postfix &other) const
{
  return arith_operator_impl(other, "*");
}

sveshnikov::Postfix &sveshnikov::Postfix::arith_operator_impl(Postfix other, std::string op) const
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

long long sveshnikov::Postfix::calculate() const noexcept
{
  constexpr long long max_ll = std::numeric_limits<long long>::max();
  constexpr long long min_ll = std::numeric_limits<long long>::min();
  Stack< long long > stack;
  Queue< std::string > queue(expr_);
  for (size_t i = 1; i < queue.getSize(); i++)
  {
    std::string curr = std::move(queue.front());
    queue.pop();
    if (curr == "+" || curr == "-" || curr == "/" || curr == "%" || curr == "*")
    {
      const long long operand2 = stack.top();
      stack.pop();
      long long result = stack.top();
      stack.pop();
      if (curr == "+")
      {
        if (result > max_ll - operand2)
        {
          throw std::overflow_error("ERROR: Overflow when calculating the amount!");
        }
        result += operand2;
      }
      if (curr == "-")
      {
        if (result < min_ll + operand2)
        {
          throw std::underflow_error("ERROR: Underflow when calculating the difference!");
        }
        result -= operand2;
      }
      if (curr == "/")
      {
        isDivisionByZero(operand2);
        result /= operand2;
      }
      if (curr == "%")
      {
        isDivisionByZero(operand2);
        result %= operand2;
      }
      if (curr == "*")
      {
        
        if (result > max_ll / operand2)
        {
          throw std::overflow_error("ERROR: Overflow when calculating the product!");
        }
        else if (result < min_ll / operand2)
        {
          throw std::underflow_error("ERROR: Underflow when calculating the product!");
        }
        result *= operand2;
      }
      stack.push(result);
    }
    else
    {
      stack.push(std::stoll(curr));
    }
  }
  return stack.top();
}

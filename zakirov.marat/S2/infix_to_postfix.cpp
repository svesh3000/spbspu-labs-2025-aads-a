#include "infix_to_postfix.hpp"
#include <cstddef>
#include "stack.hpp"
#include "queue.hpp"

bool zakirov::check_operand(const std::string & line)
{
  size_t dot_counter = 0;
  std::string::const_iterator fillable_it = line.cbegin();
  if (*fillable_it == '-' || *fillable_it == '+')
  {
    ++fillable_it;
  }

  for (; fillable_it != line.end(); ++fillable_it)
  {
    if (*fillable_it == '.')
    {
      ++dot_counter;
    }
    else if (!isdigit(*fillable_it))
    {
      throw std::invalid_argument("Incorrect element of expression");
    }
  }

  if (dot_counter > 1)
  {
    throw std::invalid_argument("Incorrect element of expression");
  }

  return 1;
}

bool zakirov::check_operator(std::string symbol)
{
  constexpr char operators[4] = {'+', '-', '*', '/'};
  for (size_t i = 0; i < 4; ++i)
  {
    if (symbol.front() == operators[i] && symbol.size() == 1)
    {
      return 1;
    }
  }

  return 0;
}

bool zakirov::check_priority(std::string symbol)
{
  if (symbol == "*" || symbol == "/")
  {
    return 1;
  }

  return 0;
}

zakirov::Stack< std::string > zakirov::transform_to_postfix(Queue< std::string > infix)
{
  Stack< std::string > op_buffer;
  Stack< std::string > result;

  for (size_t i = 0; i < infix.size(); ++i)
  {
    std::string symbol = infix.front();
    infix.pop();
    if (check_operand(symbol))
    {
      result.push(symbol);
    }
    else if (check_operator(symbol))
    {
      while (!op_buffer.empty() && check_priority(symbol) <= check_priority(op_buffer.top()))
      {
        result.push(op_buffer.top());
        op_buffer.pop();
      }

      op_buffer.push(symbol);
    }
    else if (symbol == "(")
    {
      op_buffer.push(symbol);
    }
    else if (symbol == ")")
    {
      while (op_buffer.top() != "(" && !op_buffer.empty())
      {
        result.push(op_buffer.top());
        op_buffer.pop();
      }

      if (!op_buffer.empty())
      {
        op_buffer.pop();
      }
      else
      {
        throw std::invalid_argument("Incorrect placement of brackets");
      }
    }
    else
    {
      throw std::invalid_argument("Incorrect expression");
    }
  }

  while (!op_buffer.empty())
  {
    if (op_buffer.top() != "(")
    {
      result.push(op_buffer.top());
      op_buffer.pop();
    }
    else
    {
      throw std::invalid_argument("Incorrect placement of brackets");
    }
  }

  return result;
}

double zakirov::transform_to_double(const std::string & line)
{
  Stack< char > num_buffer;
  std::string::const_iterator fillable_it = line.cbegin();
  double result = 0;
  for (; *fillable_it != '.' && fillable_it != line.end(); ++fillable_it)
  {
    num_buffer.push(*fillable_it);
  }

  size_t size_b = num_buffer.size();
  for (size_t i = 1; i < size_b; ++i)
  {
    result += num_buffer.top() * 10 * i;
    num_buffer.pop();
  }

  if (*fillable_it == '.')
  {
    ++fillable_it;
  }

  for (size_t i = 1; fillable_it != line.end(); ++fillable_it, ++i)
  {
    result += *fillable_it / 10 * i;
  }

  return result;
}

double zakirov::calculate_postfix(double first, double second, char oper)
{
  if (oper == '/')
  {
    return second / first;
  }
  else if (oper == '*')
  {
    return second * first;
  }
  else if (oper == '-')
  {
    return second - first;
  }
  
  return second + first;
}

double zakirov::calculate_postfix_expression(Queue< std::string > postfix)
{
  Stack< double > result;
  for (size_t i = 0; i < postfix.size(); ++i)
  {
    if (check_operand(postfix.front()))
    {
      result.push(transform_to_double(postfix.front()));
      postfix.pop();
    }
    else if (check_operator(postfix.front()))
    {
      double first = result.top();
      result.pop();
      double second = result.top();
      result.pop();
      result.push(calculate_postfix(first, second, postfix.front().front()));
      postfix.pop();
    }
  }

  if (result.size() != 1)
  {
    throw std::invalid_argument("Incorrect expression");
  }

  return result.top();
}

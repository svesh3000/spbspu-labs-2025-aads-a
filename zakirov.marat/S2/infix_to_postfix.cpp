#include "infix_to_postfix.hpp"
#include <cstddef>
#include "stack.hpp"
#include "queue.hpp"

bool zakirov::check_operand(char symbol)
{
  for (char i = '0'; i <= '9'; ++i)
  {
    if (symbol == i)
    {
      return 1;
    }
  }

  return 0;
}

bool zakirov::check_operator(char symbol)
{
  constexpr char operators[4] = {'+', '-', '*', '/'};
  for (size_t i = 0; i < 4; ++i)
  {
    if (symbol == operators[i])
    {
      return 1;
    }

    return 0;
  }
}

bool zakirov::check_priority(char symbol)
{
  if (symbol == '*' || symbol == '/')
  {
    return 1;
  }

  return 0;
}

zakirov::Stack< char > zakirov::transform_to_postfix(Queue< char > expression)
{
  Stack< char > op_buffer;
  Stack< char > result;

  for (size_t i = 0; i < expression.size(); ++i)
  {
    char symbol = expression.front();
    expression.pop();
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
    else if (symbol == '(')
    {
      op_buffer.push(symbol);
    }
    else if (symbol == ')')
    {
      while (op_buffer.top() != '(' && !op_buffer.empty())
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
      throw std::invalid_argument("Expression is incorrect");
    }
  }

  while (!op_buffer.empty())
  {
    if (op_buffer.top() != '(')
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

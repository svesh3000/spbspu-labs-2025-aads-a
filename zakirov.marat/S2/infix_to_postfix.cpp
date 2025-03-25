#include "infix_to_postfix.hpp"
#include <cstddef>

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

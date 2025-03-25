#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP
#include "queue.hpp"
#include "stack.hpp"

namespace zakirov
{
  bool check_operand(char symbol);
  bool check_operator(char symbol);
  bool check_priority(char symbol);
  Stack< char > transform_to_postfix(Queue< char > expression);
}

#endif


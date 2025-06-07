#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP
#include <string>
#include "queue.hpp"
#include "stack.hpp"

namespace zakirov
{
  bool check_operand(const std::string & line);
  bool check_operator(std::string symbol);
  bool check_priority(std::string symbol);
  void check_overflow(long long first, long long second, char oper);
  Queue< std::string > transform_to_postfix(Queue< std::string > & infix);
  long long transform_to_llint(const std::string & line);
  long long calculate_postfix(long long first, long long second, char oper);
  long long calculate_postfix_expression(const Queue< std::string > & infix);
}

#endif

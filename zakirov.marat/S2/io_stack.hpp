#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP
#include <iostream>
#include "queue.hpp"
#include "stack.hpp"

namespace zakirov
{
  void get_infix(std::istream & in);
  void output_results(std::ostream & out, Stack< double > & results);
}

#endif


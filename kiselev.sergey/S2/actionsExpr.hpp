#ifndef ACTIONSEXPR_HPP
#define ACTIONSEXPR_HPP
#include "queue.hpp"
#include "stack.hpp"
#include <string>

namespace kiselev
{
  using queue = Queue< std::string >;
  using stack = Stack< std::string >;
  using stackNumber = Stack< long long int >;
  queue convertExpr(queue& infix);
  stackNumber calculationExpr(queue& postfix);
}
#endif

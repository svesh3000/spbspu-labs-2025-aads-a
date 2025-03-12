#ifndef EXPR_CONVERT_HPP
#define EXPR_CONVERT_HPP
#include <string>
#include <queue.hpp>
#include <stack.hpp>

namespace demehin
{
  using ExprQueue = demehin::Queue< std::string >;
  using ExprsStack = demehin::Stack< ExprQueue >;
  void convertStack(ExprsStack& infExprs, ExprsStack& postExprs);
  ExprQueue convertQueue(ExprQueue& infExpr);
  int calculateExpr(const ExprQueue& expr);
  void getExprsValues(ExprsStack postStack, Stack< int >& values);
}

#endif

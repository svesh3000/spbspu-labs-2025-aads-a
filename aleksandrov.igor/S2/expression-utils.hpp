#ifndef EXPRESSION_UTILS_HPP
#define EXPRESSION_UTILS_HPP

#include <ios>
#include "stack.hpp"
#include "queue.hpp"
#include "expression-part.hpp"

namespace aleksandrov
{
  using Expression = Queue< ExpressionPart >;
  using Expressions = Queue< Expression >;

  std::istream& operator>>(std::istream&, ExpressionPart&);

  void getExpressions(std::istream& in, Expressions& dest);

  Expression getPostfixForm(Expression&);
  void getPostfixForms(Expressions& src, Expressions& dest);

  OperandType performOperation(OperationType, OperandType, OperandType);
  OperandType evalPostfixExpression(Expression&);
  void evalPostfixExpressions(Expressions& src, Stack< OperandType >& dest);
}

#endif


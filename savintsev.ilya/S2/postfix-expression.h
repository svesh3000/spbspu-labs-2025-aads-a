#ifndef POSTFIX_EXPRESSION_H
#define POSTFIX_EXPRESSION_H
#include <string>
#include <queue>
#include <stack>

namespace savintsev
{
  class PostfixExpr
  {
  public:
    PostfixExpr(std::string infix_expr);

    PostfixExpr operator+(PostfixExpr rhs);
    PostfixExpr operator-(PostfixExpr rhs);
    PostfixExpr operator/(PostfixExpr rhs);
    PostfixExpr operator*(PostfixExpr rhs);
    PostfixExpr operator%(PostfixExpr rhs);
  private:
    std::queue< std::string > expr_;
    //std::stack< std::string > pstack_;
  };

  bool is_token_number(std::string token);
}

#endif

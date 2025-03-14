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
    PostfixExpr() = default;
    PostfixExpr(PostfixExpr & rhs);

    void operator=(std::string & infix_expr);

    int get_result() const;

    PostfixExpr operator+(PostfixExpr rhs);
    PostfixExpr operator-(PostfixExpr & rhs);
    PostfixExpr operator/(PostfixExpr & rhs);
    PostfixExpr operator*(PostfixExpr & rhs);
    PostfixExpr operator%(PostfixExpr & rhs);
  private:
    std::queue< std::string > expr_;
    int result_ = 0;
    void calculate_result(std::string token, std::stack< int > & calc) const;
    bool is_token_number(std::string token);
  };
}

#endif

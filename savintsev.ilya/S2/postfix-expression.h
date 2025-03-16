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
    PostfixExpr(const PostfixExpr & rhs);
    PostfixExpr(PostfixExpr && rhs);

    long long operator()() const;

    PostfixExpr & operator=(const PostfixExpr & rhs);

    PostfixExpr operator+(const PostfixExpr & rhs);
    PostfixExpr operator-(const PostfixExpr & rhs);
    PostfixExpr operator*(const PostfixExpr & rhs);
    PostfixExpr operator/(const PostfixExpr & rhs);
    PostfixExpr operator%(const PostfixExpr & rhs);

    friend PostfixExpr convert(const std::string & infix);
  private:
    std::queue< std::string > expr_;

    PostfixExpr & use_operator(const std::string & op, PostfixExpr rhs);
  };

  PostfixExpr convert(const std::string & infix);
}

#endif

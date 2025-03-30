#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include <string>
#include "queue.hpp"

namespace sveshnikov
{
  class Postfix
  {
  public:
    Postfix() = default;
    Postfix(const Postfix &other);
    Postfix(Postfix &&other);
    ~Postfix() = default;
    Postfix &operator=(const Postfix &other);
    Postfix &operator=(Postfix &&other) noexcept;

    Postfix &operator+(const Postfix &other) const;
    Postfix &operator-(const Postfix &other) const;
    Postfix &operator/(const Postfix &other) const;
    Postfix &operator%(const Postfix &other) const;
    Postfix &operator*(const Postfix &other) const;

    long long calculate() const noexcept;

  private:
    Queue< std::string > expr_;
    Postfix &arith_operator_impl(Postfix other, std::string op) const;
  };
}

#endif

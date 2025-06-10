#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include <string>
#include "queue.hpp"

namespace zakirov
{
  class Postfix
  {
  public:
    Postfix() = default;
    Postfix(const Postfix & other) = default;
    Postfix(Postfix && other) = default;
    Postfix(const std::string & infix);
    ~Postfix() = default;
    Postfix & operator=(const Postfix & other) = default;
    Postfix operator+(const Postfix & other);
    Postfix operator-(const Postfix & other);
    Postfix operator*(const Postfix & other);
    Postfix operator/(const Postfix & other);
    Postfix operator%(const Postfix & other);
    long long operator()();
  private:
    Postfix unite_postfixes(const Postfix & other);
    Queue< std::string > postfix;
  };
}

#endif

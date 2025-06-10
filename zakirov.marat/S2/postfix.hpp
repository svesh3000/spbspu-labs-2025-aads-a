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
    Postfix(const std::string & infix);
    Postfix & operator+(const Postfix & other);
    Postfix & operator-(const Postfix & other);
    Postfix & operator*(const Postfix & other);
    Postfix & operator/(const Postfix & other);
    Postfix & operator%(const Postfix & other);
    long long operator()();
  private:
    Postfix & unite_postfixes(const Postfix & other);
    Queue< std::string > postfix;
  };
}

#endif

#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include <string>
#include "queue.hpp"

namespace sveshnikov
{
  class Postfix
  {
  public:
    explicit Postfix();
    Postfix(const Postfix &other);
    Postfix(Postfix &&other);
    ~Postfix();
    Postfix &operator=(const Postfix &other);
    Postfix &operator=(Postfix &&other) noexcept;

    Postfix &operator+(const Postfix &other);
    Postfix &operator/(const Postfix &other);
    Postfix &operator-(const Postfix &other);
    Postfix &operator*(const Postfix &other);

  private:
    Queue< std::string > queue;
  };
}

#endif

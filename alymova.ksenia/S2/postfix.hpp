#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include <string>
#include "queue.hpp"

namespace alymova
{
  struct Postfix
  {
    Postfix(const std::string& s);

    long long int operator()();
    long long int operator+(const Postfix& other);
    long long int operator-(const Postfix& other);
    long long int operator*(const Postfix& other);
    long long int operator/(const Postfix& other);
    long long int operator%(const Postfix& other);
  private:
    Queue< std::string > postfix_;

    void push_operator(Postfix other, std::string operation);
  };
}
#endif

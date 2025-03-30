#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include <string>
#include "queue.hpp"

namespace alymova
{
  struct Postfix
  {
    //Postfix() = default;
    //Postfix(const Postfix& other) = default;
    //Postfix(Postfix&& other) = default;
    Postfix(const std::string& s);
    //~Postfix() = default;

    long long int operator()();
    long long int operator+(const Postfix& other);
    long long int operator-(const Postfix& other);
    long long int operator*(const Postfix& other);
    long long int operator/(const Postfix& other);
    long long int operator%(const Postfix& other);
  private:
    Queue< std::string > postfix_;

    void push(Postfix other);
  };
}
#endif

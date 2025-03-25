#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include "queue.hpp"

namespace alymova
{
  Queue< std::string > convert_postfix(const std::string& s);
  long long int count_postfix(alymova::Queue< std::string >& queue);
  bool my_isdigit(const std::string& s);
  bool is_overflow_addition(long long int lhs, long long int rhs);
  bool is_overflow_multi(long long int lhs, long long int rhs);
}
#endif

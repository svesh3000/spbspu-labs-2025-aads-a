#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include "queue.hpp"

namespace alymova
{
  Queue< std::string > convert_postfix(const std::string& s);
  long long int count_postfix(alymova::Queue< std::string >& queue);
  bool my_isdigit(const std::string& s);
}
#endif

#include "key_sum.hpp"
#include <limits>
#include <stdexcept>

void smirnov::KeySum::operator()(const std::pair< const int, std::string > & value)
{
  bool overflow = (result > 0 && value.first > std::numeric_limits< int >::max() - result);
  bool underflow = (result < 0 && value.first < std::numeric_limits< int >::min() - result);
  if (overflow || underflow)
  {
    throw std::overflow_error("overflow");
  }
  result += value.first;
  elems += ' ' + value.second;
}

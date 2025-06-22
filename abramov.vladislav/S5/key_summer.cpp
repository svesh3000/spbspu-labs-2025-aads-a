#include "key_summer.hpp"
#include <limits>
#include <stdexcept>

void abramov::KeyAdder::operator()(const std::pair< long long int, std::string > p)
{
  long long int curr = p.first;
  if (curr > 0 && res > std::numeric_limits< long long int >::max() - curr)
  {
    throw std::logic_error("Overflow\n");
  }
  else if (curr < 0 && res < std::numeric_limits< long long int >::min() - curr)
  {
    throw std::logic_error("Overflow\n");
  }
  res += curr;
  val += " ";
  val += p.second;
}

#ifndef KEY_SUMMER_HPP
#define KEY_SUMMER_HPP
#include <pair>

namespace abramov
{
  struct KeySummer
  {
    long long int res = 0;
    std::string val;

    void operator()(const std::pair< long long int, std::string > p);
  }
}
#endif

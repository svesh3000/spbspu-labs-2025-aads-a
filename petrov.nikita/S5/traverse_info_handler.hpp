#ifndef TRAVERSE_INFO_HANDLER_HPP
#define TRAVERSE_INFO_HANDLER_HPP

#include <functional>
#include <string>

namespace petrov
{
  struct SumUpKeys
  {
    int result = 0;
    void operator()(const std::pair< const int, std::string > & key_value);
  };
}

#endif

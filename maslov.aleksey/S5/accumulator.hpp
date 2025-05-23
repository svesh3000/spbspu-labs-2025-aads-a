#ifndef KEY_SUM_HPP
#define KEY_SUM_HPP

#include <string>

namespace maslov
{
  struct KeyValueAccumulator
  {
    KeyValueAccumulator();
    int keySum;
    std::string values;
    void operator()(const std::pair< int, std::string > & keyValue);
  };
}

#endif

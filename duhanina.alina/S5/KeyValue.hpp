#ifndef KEYVALUE_HPP
#define KEYVALUE_HPP

#include <string>
#include <utility>

namespace duhanina
{
  struct KeySum
  {
    long long result = 0;
    void operator()(const std::pair< const long long, std::string >& key_value);
  };

  struct ValueCollector
  {
    std::string result;
    void operator()(const std::pair< const long long, std::string >& key_value);
  };
}

#endif

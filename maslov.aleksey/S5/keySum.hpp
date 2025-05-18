#ifndef KEY_SUM_HPP
#define KEY_SUM_HPP

#include <string>

namespace maslov
{
  struct KeySum
  {
    int key;
    std::string value;
    void operator()(const std::pair< int, std::string > & pairKeyValue);
  };
}

#endif

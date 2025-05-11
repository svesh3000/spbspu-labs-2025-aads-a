#ifndef KEY_ADDER_HPP
#define KEY_ADDER_HPP
#include <limits>
#include <stdexcept>

namespace savintsev
{
  struct KeyAdder
  {
    void operator()(const std::pair< long long, std::string > val)
    {
      if (val.first > 0 && result_ > std::numeric_limits< long long >::max() - val.first)
      {
        throw std::overflow_error("Key sum overflow (positive)");
      }
      else if (val.first < 0 && result_ < std::numeric_limits< long long >::min() - val.first)
      {
        throw std::overflow_error("Key sum overflow (negative)");
      }

      result_ += val.first;
      values_ += " " + val.second;
    }

    long long result_ = 0;
    std::string values_;
  };
}

#endif

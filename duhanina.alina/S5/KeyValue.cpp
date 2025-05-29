#include "KeyValue.hpp"
#include <limits>
#include <stdexcept>

void duhanina::KeySum::operator()(const std::pair< const long long, std::string >& key_value)
{
  if (result > 0 && key_value.first > std::numeric_limits< long long >::max() - result)
  {
    throw std::overflow_error("Key sum overflow");
  }
  if (result < 0 && key_value.first < std::numeric_limits< long long >::min() - result)
  {
    throw std::overflow_error("Key sum underflow");
  }
  result += key_value.first;
}

void duhanina::ValueCollector::operator()(const std::pair< const long long, std::string >& key_value)
{
  if (!result.empty())
  {
    result += " ";
  }
  result += key_value.second;
}

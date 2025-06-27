#include "traverse_info_handler.hpp"

void petrov::SumUpKeysDisplayValues::operator()(const std::pair< const int, std::string > & key_val)
{
  result += key_val.first;
  queue_.push(key_val.second);
}

std::ostream & petrov::SumUpKeysDisplayValues::displayValuesInTraverseOrder(std::ostream & out)
{
  out << queue_.front();
  queue_.pop();
  while (!queue_.empty())
  {
    out << ' ' << queue_.front();
    queue_.pop();
  }
  return out;
}

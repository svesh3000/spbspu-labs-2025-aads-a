#include "traverse_info_handler.hpp"

void petrov::SumUpKeys::operator()(const std::pair< const int, std::string > & key_val)
{
  result += key_val.first;
}

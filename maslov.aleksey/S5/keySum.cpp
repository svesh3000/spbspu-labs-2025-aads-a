#include "keySum.hpp"

void maslov::KeyValueAccumulator::operator()(const std::pair< int, std::string > & keyValue)
{
  keySum += keyValue.first;
  if (!values.empty())
  {
    values += ' ';
  }
  values += keyValue.second;
}

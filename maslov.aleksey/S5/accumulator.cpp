#include "accumulator.hpp"

maslov::KeyValueAccumulator::KeyValueAccumulator():
  keySum(0),
  values()
{}

void maslov::KeyValueAccumulator::operator()(const std::pair< int, std::string > & keyValue)
{
  keySum += keyValue.first;
  if (!values.empty())
  {
    values += ' ';
  }
  values += keyValue.second;
}

#include "print_results.hpp"
#include <limits>

void smirnov::printName(std::ostream & out, const List< std::pair< std::string, List< size_t > > > & sequences)
{
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    if (it != sequences.cbegin())
    {
      out << " ";
    }
    out << it->first;
  }
  out << "\n";
}

void smirnov::printSequences(std::ostream & out, const List< List< size_t > > & sequences)
{
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    for (auto numIt = it->cbegin(); numIt != it->cend(); ++numIt)
    {
      if (numIt != it->cbegin())
      {
        out << " ";
      }
      out << *numIt;
    }
    out << "\n";
  }
}

void smirnov::printSums(std::ostream & out, const List< List< size_t > > & sequences)
{
  List< size_t > sums;
  for (auto it = sequences.cbegin(); it != sequences.cend(); ++it)
  {
    size_t sum = 0;
    for (auto numIt = it->cbegin(); numIt != it->cend(); ++numIt)
    {
      if (sum > std::numeric_limits< size_t >::max() - *numIt)
      {
        throw std::overflow_error("Overflow!");
      }
      sum += *numIt;
    }
    sums.push_back(sum);
  }
  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    if (it != sums.begin())
    {
      out << " ";
    }
    out << *it;
  }
  out << "\n";
}

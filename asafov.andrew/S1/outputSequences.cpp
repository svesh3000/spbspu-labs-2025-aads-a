#include "sequencefunctions.h"

namespace
{
  bool allItersEnds(asafov::data_list_t::const_iterator* begins, asafov::data_list_t::const_iterator* ends, size_t size)
  {
    for (size_t i = 0; i < size; i++)
    {
      if(begins[i]!=ends[i])
      {
        return false;
      }
    }
    return true;
  }
}

void asafov::outputSequences(sequence_list_t& sequences, std::ostream& out = std::cout)
{
  if (sequences.cbegin()->second.empty())
  {
    std::cout << sequences.cbegin()->first << "\n0\n";
    return;
  };
  data_list_t::const_iterator* begins = new data_list_t::const_iterator[sequences.size()];
  data_list_t::const_iterator* ends = new data_list_t::const_iterator[sequences.size()];
  sequence_list_t::const_iterator seqiter = sequences.cbegin();
  size_t size = 0;
  auto ii = sequences.cbegin();
  out << ii->first << ' ';
  begins[size] = ii->second.cbegin();
  ends[size] = ii->second.cend();
  ++size;
  for (; ii != sequences.cend(); ++ii)
  {
    out << ' ' << ii->first;
    begins[size] = ii->second.cbegin();
    ends[size] = ii->second.cend();
    ++size;
  }
  if (sequences.size() != 0)
  {
    out << '\n';
  }
  seqiter = sequences.cbegin();
  data_list_t sums;
  while (!::allItersEnds(begins, ends, size))
  {
    data_t sum = 0;
    if (begins[0] != ends[0])
    {
      sum += *begins[0];
      if (sum < *begins[0]) throw std::overflow_error("owerflow!");
      out << *begins[0] << ' ';
      ++begins[0];
    }
    for (size_t i = 1; i < sequences.size();)
    {
      if (begins[i] != ends[i])
      {
        sum += *begins[i];
        if (sum < *begins[i]) throw std::overflow_error("owerflow!");
        out << *begins[i] << ' ';
        ++begins[i++];
      }
      else
      {
        i++;
      }
    }
    std::cout << '\n';
    sums.push_back(sum);
  }

  auto it = sums.cbegin();
  out << *it;
  ++it;
  for (; it != sums.cend(); ++it) out << ' ' << *it;

  if (sequences.size() != 0) out << '\n';

  delete[] begins;
  delete[] ends;
}

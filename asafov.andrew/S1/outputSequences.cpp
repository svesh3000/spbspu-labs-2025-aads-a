#include "sequencefunctions.h"
#include <limits>
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
  for (auto iter = sequences.cbegin(); iter != sequences.cend(); ++iter)
  {
    out << iter->first << ' ';
    begins[size] = iter->second.cbegin();
    ends[size] = iter->second.cend();
    ++size;
  }
  if (sequences.size() != 0)
  {
    out << '\n';
  }
  seqiter = sequences.cbegin();
  data_list_t sums;
  while (!allItersEnds(begins, ends, size))
  {
    data_t sum = 0;
    for (size_t i = 0; i < sequences.size();)
    {
      if (begins[i] != ends[i])
      {
        if (sum > std::numeric_limits<data_t>::max() - *begins[i])
        {
          sums.clear();
          delete[] begins;
          delete[] ends;
          throw std::overflow_error("owerflow!");
        }
        else
        {
          sum += *begins[i];
        }
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
  for (auto it = sums.cbegin(); it != sums.cend(); ++it)
  {
    out << *it << ' ';
  }
  if (sequences.size() != 0)
  {
    out << '\n';
  }
  delete[] begins;
  delete[] ends;
}

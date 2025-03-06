#include "sequencefunctions.h"
#include <algorithm>

static bool allItersEnds(data_list_t::const_iterator* begins, data_list_t::const_iterator* ends, size_t size)
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

sequence_list_t asafov::getSequences(std::istream& in)
{
  sequence_list_t data;
  do
  {
    std::string name;
    data_list_t list;
    data_t temp = 0;
    in >> name;
    while (!in.fail())
    {
      in >> temp;
      if (in.fail())
      {
        break;
      }
      list.push_back(temp);
    }
    if (!in.eof())
    {
      in.clear();
    }
    sequence_t pair = make_pair(name, list);
    data.push_back(pair);
  } while (!in.eof());
  return data;
}

void asafov::outputSequences(sequence_list_t& sequences, std::ostream& out)
{
  data_list_t::const_iterator* begins = new data_list_t::const_iterator[sequences.size()];
  data_list_t::const_iterator* ends = new data_list_t::const_iterator[sequences.size()];
  sequence_list_t::const_iterator seqiter = sequences.cbegin();
  size_t size = 0;
  for (auto iter = sequences.cbegin(); iter != sequences.cend(); ++iter)
  {
    std::cout << iter->first << ' ' << std::flush;
    begins[size] = iter->second.cbegin();
    ends[size] = iter->second.cend();
    ++size;
  }
  std::cout << '\n';
  seqiter = sequences.cbegin();
  data_list_t sums;
  while (!allItersEnds(begins, ends, sequences.size()))
  {
    data_t sum = 0;
    for (size_t i = 0; i < sequences.size(); i++)
    {
      if (begins[i] != ends[i])
      {
        sum += *begins[i];
        std::cout << *begins[i] << ' ' << std::flush;
        ++begins[i];
      }
    }
    sums.push_back(sum);
    std::cout << '\n';
  }
  for (auto it = sums.cbegin(); it != sums.cend(); ++it)
  {
    std::cout << *it << ' ' << std::flush;
  }
  std::cout << '\n';
  delete[] begins;
  delete[] ends;
}

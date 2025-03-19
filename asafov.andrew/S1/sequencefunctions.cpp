#include "sequencefunctions.h"
#include <stdexcept>

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

void asafov::getSequences(sequence_list_t& sequences, std::istream& in)
{
  std::cout << "getSequences(begin)" << std::endl;
  do
  {
    std::string name;
    data_list_t* list = new data_list_t;
    data_t temp = 0;
    in >> name;
    while (!in.fail())
    {
      in >> temp;
      if (in.fail())
      {
        break;
      }
      list->push_back(temp);
    }
    if (!in.eof())
    {
      in.clear();
    }
    sequences.push_back(sequence_t(name, list));
  } while (!in.eof());
  std::cout << "getSequences(end)" << std::endl;
}

void asafov::outputSequences(sequence_list_t& sequences, std::ostream& out)
{
  std::cout << "outputSequences(begin)" << std::endl;
  data_list_t::const_iterator* begins = new data_list_t::const_iterator[sequences.size()];
  data_list_t::const_iterator* ends = new data_list_t::const_iterator[sequences.size()];
  sequence_list_t::const_iterator seqiter = sequences.cbegin();
  size_t size = 0;
  for (auto iter = sequences.cbegin(); iter != sequences.cend(); ++iter)
  {
    out << iter->first << ' ' << std::flush;
    begins[size] = iter->second->cbegin();
    ends[size] = iter->second->cend();
    ++size;
  }
  if (sequences.size() != 0)
  {
    out << '\n';
  }
  seqiter = sequences.cbegin();
  data_list_t sums;
  while (!allItersEnds(begins, ends, sequences.size()))
  {
    data_t sum = 0;
    for (size_t i = 0; i < sequences.size();)
    {
      if (begins[i] != ends[i])
      {
        sum += *begins[i];////////////////////////
        out << *begins[i] << ' ';////////////
        ++begins[i++];
      }
    }
    sums.push_back(sum);
    out << '\n';
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
  std::cout << "outputSequences(end)" << std::endl;
}

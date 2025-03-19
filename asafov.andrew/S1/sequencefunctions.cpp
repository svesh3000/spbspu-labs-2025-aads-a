#include "sequencefunctions.h"
#include <stdexcept>

#define var_name(var) #var

static bool allItersEnds(data_list_t::const_iterator* begins, data_list_t::const_iterator* ends, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    if(begins[i]!=ends[i])
    {
      std::cout << RED << "allitersend(false)\n"  << RESET<< std::flush;
      return false;
    }
  }
  std::cout << RED << "allitersend(true)\n"  << RESET<< std::flush;
  return true;
}

void asafov::getSequences(sequence_list_t& sequences, std::istream& in)
{
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
      std::cout << RED << var_name(temp) << ' ' << RESET << std::flush;
      list.push_back(temp);
    }
    if (!in.eof())
    {
      in.clear();
    }
    sequence_t pair = std::make_pair(name, list);
    std::cout << RED << var_name(pair) << ' '  << RESET<< std::flush;
    sequences.push_back(pair);
  } while (!in.eof());
}

void asafov::outputSequences(sequence_list_t& sequences, std::ostream& out)
{
  std::cout << RED << "outputSequences(begin)" << RESET << std::endl;
  data_list_t::const_iterator* begins = new data_list_t::const_iterator[sequences.size()];
  data_list_t::const_iterator* ends = new data_list_t::const_iterator[sequences.size()];
  sequence_list_t::const_iterator seqiter = sequences.cbegin();
  size_t size = 0;
  for (auto iter = sequences.cbegin(); iter != sequences.cend(); ++iter)
  {
    out << iter->first << ' ' << std::flush;
    begins[size] = iter->second.cbegin();
    ends[size] = iter->second.cend();
    ++size;
  }
  if (sequences.size() != 0)
  {
    out << '\n' << std::flush;
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
        sum += *begins[i];////////////////////////
        out << *begins[i] << ' ' << std::flush;////////////
        ++begins[i++];
      }
      else
      {
        i++;
      }
    }
    std::cout << '\n' << RED << var_name(sum) << RESET  << ' '<< std::flush;
    sums.push_back(sum);
  }
  for (auto it = sums.cbegin(); it != sums.cend(); ++it)
  {
    out << *it << ' ' << std::flush;
  }
  if (sequences.size() != 0)
  {
    out << '\n' << std::flush;
  }
  delete[] begins;
  delete[] ends;
  std::cout << RED << "outputSequences(end)\n" << RESET << std::flush;
}

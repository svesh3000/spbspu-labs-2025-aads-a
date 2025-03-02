#include "io-sequences.hpp"
#include <iostream>
#include <iterator>
#include <limits>
#include "list-manip.hpp"

namespace
{
  void inputOneList(std::istream &in, list_ull_t &data);
  std::ostream &outputOneList(std::ostream &out, const list_pair_t &list, size_t size);
  unsigned long long findSum(const list_pair_t &list, size_t size);

  void inputOneList(std::istream &in, list_ull_t &data)
  {
    unsigned long long num = 0;
    list_ull_t data_copied = data;
    while (in >> num)
    {
      try
      {
        data_copied.push_front(num);
      }
      catch (std::bad_alloc &e)
      {
        data_copied.clear();
        throw;
      }
    }
    if (in.fail() && !in.eof())
    {
      in.clear();
    }
    for (iter_list_ull_t it = data_copied.cbegin(); it != data_copied.cend(); it++)
    {
      try
      {
        data.push_front(*it);
      }
      catch (std::bad_alloc &e)
      {
        data_copied.clear();
        data.clear();
        throw;
      }
    }
  }

  std::ostream &outputOneList(std::ostream &out, const list_pair_t &list, size_t size)
  {
    bool first = true;
    for (iter_t it = list.cbegin(); it != list.cend(); it++)
    {
      if (size >= getSizeList(it))
      {
        continue;
      }
      iter_list_ull_t it_data = it->second.cbegin();
      for (size_t i = 0; i < size; i++)
      {
        it_data++;
      }
      if (first)
      {
        first = false;
        out << *it_data;
        continue;
      }
      out << " " << *it_data;
    }
    return out;
  }

  unsigned long long findSum(const list_pair_t &list, size_t size)
  {
    unsigned long long sum = 0;
    for (iter_t it = list.cbegin(); it != list.cend(); it++)
    {
      if (size >= sveshnikov::getSizeDataList(it))
      {
        continue;
      }
      iter_list_ull_t it_data = it->second.cbegin();
      for (size_t i = 0; i < size; i++)
      {
        it_data++;
      }
      if (sum > std::numeric_limits< unsigned long long >::max() - *it_data)
      {
        throw std::overflow_error("ERROR: Overflow when calculating the amount!");
      }
      sum += *it_data;
    }
    return sum;
  }
}

void sveshnikov::inputLists(std::istream &in, list_pair_t &list)
{
  std::string name_sequence;
  list_pair_t list_reverse;
  while (!in.eof())
  {
    in >> name_sequence;
    list_ull_t data_sequence;
    inputOneList(in, data_sequence);
    pair_t sequence = {name_sequence, data_sequence};
    list_reverse.push_front(sequence);
  }
  for (iter_t it = list_reverse.cbegin(); it != list_reverse.cend(); it++)
  {
    list.push_front(*it);
  }
}

std::ostream &sveshnikov::outputNamesLists(std::ostream &out, const list_pair_t &list)
{
  out << list.cbegin()->first;
  for (iter_t it = ++list.cbegin(); it != list.cend(); it++)
  {
    out << " " << it->first;
  }
  return out;
}

std::ostream &sveshnikov::outputNewLists(std::ostream &out, const list_pair_t &list)
{
  size_t num_new_lists = getNumNewLists(list.cbegin(), list.cend());
  size_t size_list = 0;
  while (size_list + 1 != num_new_lists)
  {
    outputOneList(out, list, size_list) << '\n';
    size_list++;
  }
  outputOneList(out, list, size_list);
  return out;
}

std::ostream &sveshnikov::outputSumsNewLists(std::ostream &out, const list_pair_t &list)
{
  out << findSum(list, 0);
  size_t num_new_lists = getNumNewLists(list.cbegin(), list.cend());
  for (size_t size_list = 1; size_list != num_new_lists; size_list++)
  {
    out << " " << findSum(list, size_list);
  }
  return out;
}

#include "io-sequences.hpp"
#include <iostream>
#include <iterator>

namespace
{
  void inputOneList(std::istream &in, list_ull_t &data);
  std::ostream &outputOneList(std::ostream &out, const list_pair_t &list, size_t size);
  size_t getSizeList(iter_t i);
  size_t getNumNewLists(iter_t begin, iter_t end);

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
      data.push_front(*it);
    }
  }

  size_t getSizeList(iter_t i)
  {
    size_t len = 0;
    for (iter_list_ull_t j = i->second.cbegin(); j != i->second.cend(); j++)
    {
      len++;
    }
    return len;
  }

  size_t getNumNewLists(iter_t begin, iter_t end)
  {
    size_t num_lines = 0;
    for (iter_t i = begin; i != end; i++)
    {
      num_lines = std::max(num_lines, getSizeList(i));
    }
    return num_lines;
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
  return out;
}

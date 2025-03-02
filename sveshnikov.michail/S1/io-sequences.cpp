#include "io-sequences.hpp"
#include <iostream>
#include <iterator>

namespace
{
  using iter_t = sveshnikov::list_pair_t::const_iterator;
  void inputOneList(std::istream &in, std::forward_list<unsigned long long> &data);

  void inputOneList(std::istream &in, std::forward_list<unsigned long long> &data)
  {
    using iter_list_ull_t = sveshnikov::list_ull_t::const_iterator;
    unsigned long long num = 0;
    std::forward_list<unsigned long long> data_copied = data;
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
}

void sveshnikov::inputLists(std::istream &in, list_pair_t &list)
{
  std::string name_sequence;
  list_pair_t list_reverse;
  while (!in.eof())
  {
    std::cin >> name_sequence;
    list_ull_t data_sequence;
    inputOneList(std::cin, data_sequence);
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
  return out;
}

std::ostream &sveshnikov::outputSumsNewLists(std::ostream &out, const list_pair_t &list)
{
  return out;
}

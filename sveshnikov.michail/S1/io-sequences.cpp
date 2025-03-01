#include "io-sequences.hpp"
#include <iostream>

namespace
{
  void inputOneList(std::istream &in, std::forward_list< unsigned long long > &data);

  void inputOneList(std::istream &in, std::forward_list< unsigned long long > &data)
  {
    unsigned long long num = 0;
    while (in >> num)
    {
      try
      {
        data.push_front(num);
      }
      catch (std::bad_alloc &e)
      {
        data.clear();
        throw;
      }
    }
    if (in.fail() && !in.eof())
    {
      in.clear();
    }
  }
}

void sveshnikov::inputLists(std::istream &in, list_pair_t &list)
{
  std::string name_sequence;
  while (!in.eof())
  {
    std::cin >> name_sequence;
    std::forward_list< unsigned long long > data_sequence;
    inputOneList(std::cin, data_sequence);
    pair_t sequence = {name_sequence, data_sequence};
    list.push_front(sequence);
  }
}

std::ostream &sveshnikov::outputNamesLists(std::ostream &out, const list_pair_t &list)
{
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

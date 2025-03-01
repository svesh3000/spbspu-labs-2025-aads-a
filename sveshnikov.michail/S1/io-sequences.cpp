#include "io-sequences.hpp"
#include <iostream>
#include <iterator>

namespace
{
  using iterator_t = sveshnikov::list_pair_t::const_iterator;
  void inputOneList(std::istream &in, std::forward_list< unsigned long long > &data);
  std::ostream &outputNamesRecursive(std::ostream &out, iterator_t element, iterator_t end);

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

  std::ostream &outputNamesRecursive(std::ostream &out, iterator_t element, iterator_t end)
  {
    iterator_t element_copied = element;
    if (++element == end)
    {
      out << element_copied->first;
      return out;
    }
    element = element_copied;
    outputNamesRecursive(out, ++element, end);
    out << " " << element_copied->first;
    return out;
  }
}

void sveshnikov::inputLists(std::istream &in, list_pair_t &list)
{
  std::string name_sequence;
  while (!in.eof())
  {
    std::cin >> name_sequence;
    list_ull_t data_sequence;
    inputOneList(std::cin, data_sequence);
    pair_t sequence = {name_sequence, data_sequence};
    list.push_front(sequence);
  }
}

std::ostream &sveshnikov::outputNamesLists(std::ostream &out, const list_pair_t &list)
{
  using iterator_t = sveshnikov::list_pair_t::const_iterator;
  return outputNamesRecursive(out, list.cbegin(), list.cend());
}

std::ostream &sveshnikov::outputNewLists(std::ostream &out, const list_pair_t &list)
{
  return out;
}

std::ostream &sveshnikov::outputSumsNewLists(std::ostream &out, const list_pair_t &list)
{
  return out;
}

#include "manipulations_with_fwd_ring_list.hpp"

std::istream & petrov::inputValuesIntoFwdRingList(std::istream & in, my_type & fwd_ring_list)
{
  std::string sequence_num = {};
  size_t number = 0;
  while (!in.eof())
  {
    in.clear();
    in >> sequence_num;
    petrov::ForwardRingList< size_t > sublist = {};
    while (!in.eof() && in)
    {
      in >> number;
      if (!in)
      {
        break;
      }
      sublist.push_front(number);
    }
    sublist.reverse();
    fwd_ring_list.push_front({ sequence_num, sublist });
  }
  fwd_ring_list.reverse();
  return in;
}

std::ostream & petrov::outputNamesOfSuquences(std::ostream & out, const my_type & fwd_ring_list)
{
  auto it = fwd_ring_list.cbegin();
  if (fwd_ring_list.size() == 1)
  {
    out << it->first;
  }
  else
  {
    out << (it++)->first;
    do
    {
      out << " " << it->first;
    }
    while (it++ != fwd_ring_list.cend());
  }
  out << "\n";
  return out;
}

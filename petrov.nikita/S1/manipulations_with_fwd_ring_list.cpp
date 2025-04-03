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

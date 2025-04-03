#ifndef MANIPULATIONS_WITH_FWD_LIST_HPP
#define MANUPULATIONS_WITH_FWD_LIST_HPP

#include <iostream>
#include "forward_ring_list.hpp"

namespace petrov
{
  using my_type = ForwardRingList< std::pair< std::string, petrov::ForwardRingList< size_t > > >;

  std::istream & inputValuesIntoFwdRingList(std::istream & in, my_type & fwd_ring_list);
}


#endif
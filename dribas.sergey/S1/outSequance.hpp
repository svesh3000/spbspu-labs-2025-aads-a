#ifndef OUTSEQUANCE_HPP
#define OUTSEQUANCE_HPP

#include <utility>
#include <string>
#include "list.hpp"

namespace dribas
{
  void getSequanceName(std::ostream&, const List< std::pair< std::string, List< int > > >&);
}

#endif

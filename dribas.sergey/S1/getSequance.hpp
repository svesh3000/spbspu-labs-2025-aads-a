#ifndef GETSEQUANCE_HPP
#define GETSEQUANCE_HPP

#include <utility>
#include <string>
#include "list.hpp"

namespace dribas
{
  List< std::pair< std::string, List< int > > > getSequance(std::istream&);
}

#endif

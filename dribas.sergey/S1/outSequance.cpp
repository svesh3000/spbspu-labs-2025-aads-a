#include "outSequance.hpp"
#include <cstddef>
#include <iostream>

void dribas::getSequanceName(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequance)
{
  for (size_t i = 0; i < sequance.size(); i++) {
    if (i != 0) {
      out << " ";
    }
    out << sequance.at(i)->data_.first;
  }
}

// void dribas::getSequanceNameSum(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequance)
// {
//   for (size_t i = 0; i < sequance.size(); i++) {
//     for (size_t j )
//   }
// }
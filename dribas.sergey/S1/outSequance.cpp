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

void dribas::getSequanceNameSum(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequance)
{
  size_t maxSize = 0;
  for (size_t i = 0; i < sequance.size(); i++) {
    maxSize = std::max(maxSize, sequance.at(i)->data_.second.size());
  }
  dribas::List< int > sums;
  int sum = 0;  
  for (size_t i = 0; i < maxSize; i++) {
    for (size_t j = 0; j < sequance.size(); j++) {
      try {// ЭТО НЕЛЬЗЯ ТАК ОСТАВЛЯТЬ!!! ОБЯЗАТЕЛЬНО ПЕРЕДЕЛАТЬ!!!
        out << sequance.at(j)->data_.second.at(i)->data_;
        sum += sequance.at(j)->data_.second.at(i)->data_;
        if (!(j == sequance.size() - 1)) {
          out << ' ';
        }
      } catch (const std::out_of_range&) {
      }
    }
    out << '\n';
    sums.push_back(sum);
    sum = 0;
  }
  for (size_t i = 0; i < sums.size(); i++) {
    out << sums.at(i)->data_;
    if (!(i == sums.size() - 1)) {
      out << ' ';
    }
  }
}

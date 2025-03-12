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
    if (sequance.at(i)) {
      maxSize = std::max(maxSize, sequance.at(i)->data_.second.size());
    }
  }
  dribas::List< int > sums;
  int sum = 0;
  for (size_t i = 0; i < maxSize; i++) {
    bool isFirst = true;
    for (size_t j = 0; j < sequance.size(); j++) {
      if (sequance.at(j) && i < sequance.at(j)->data_.second.size()) {
        if (!isFirst) {
          out << " ";
        }
        out << sequance.at(j)->data_.second.at(i)->data_;
        sum += sequance.at(j)->data_.second.at(i)->data_;
        isFirst = false;
      }
    }
    out << '\n';
    sums.push_back(sum);
    sum = 0;
  }
  bool isFirst = true;
  for (size_t i = 0; i < sums.size(); i++) {
    if (sums.at(i)) {
      if (!isFirst) {
        out << " ";
      }
      out << sums.at(i)->data_;
      isFirst = false;
    }
  }
}
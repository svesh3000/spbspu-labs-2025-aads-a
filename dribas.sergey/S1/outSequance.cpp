#include "outSequance.hpp"
#include <cstddef>
#include <iostream>
#include <limits>

void dribas::outSequanceName(std::ostream& out, const List< std::pair< std::string, List< unsigned long long > > >& sequance)
{
  out << sequance.begin()->first;
  for (auto i = ++sequance.begin(); i != sequance.end(); i++) {
    out << ' ' << i->first;
  }
}

void dribas::outSequanceNameSum(std::ostream& out, const List< std::pair< std::string, List< unsigned long long > > >& sequance)
{
  size_t maxSize = 0;
  for (auto i = sequance.begin(); i != sequance.end(); i++) {
    if (i != sequance.end()) {
      maxSize = std::max(maxSize, i->second.size());
    }
  }
  if (maxSize == 0) {
    out << '0';
  }
  bool isOverflow = false;
  dribas::List< unsigned long long > sums;
  unsigned long long sum = 0;
  for (size_t i = 0; i < maxSize; ++i) {
    bool isFirst = true;
    for (auto j = sequance.begin(); j != sequance.end(); ++j) {
      if (j != sequance.end()  && i < j->second.size()) {
        auto it_data = j->second.begin();
        std::advance(it_data, i);
        if (!isFirst) {
          out << " ";
        }
        out << *it_data;
        sum += *it_data;
        if ((*it_data) > std::numeric_limits<int>::max()) {
          isOverflow = true;
        }
        isFirst = false;
        }
      }
      if (!(i == maxSize - 1 && isOverflow)) {
        out << '\n';
      }
      sums.push_back(sum);
      sum = 0;
  }
    if (isOverflow) {
      return;
    }
    out << *sums.begin();
    for (auto i = ++sums.begin(); i != sums.end(); i++) {
      if (i != sums.end()) {
        out << " " << *i;
      }
    }
}

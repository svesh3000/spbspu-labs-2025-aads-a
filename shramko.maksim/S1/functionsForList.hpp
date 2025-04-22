#ifndef FUNCTIONSFORLIST_HPP
#define FUNCTIONSFORLIST_HPP

#include <iostream>
#include <string>
#include <list>
#include <limits>
#include <stdexcept>
#include "list.hpp"

namespace shramko
{
  using list_t = std::list<unsigned long long>;
  using pairs_list_t = std::list<std::pair<std::string, list_t>>;

  size_t maxPairSize(const pairs_list_t& list) noexcept;
  unsigned long long getListElementSum(const list_t& list);
  void printInfo(std::ostream& out, const pairs_list_t& pairs_list);
  bool isSumOverflow(size_t a, size_t b) noexcept;
}

#endif

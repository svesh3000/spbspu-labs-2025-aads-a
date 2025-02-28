#ifndef OUTPUT_LIST_HPP
#define OUTPUT_LIST_HPP

#include <istream>
#include <forward_list>

namespace gavrilova
{
  using FLPairs = std::forward_list< std::pair< std::string, std::forward_list< int > > >;
  std::ostream& outNames(std::ostream& out, FLPairs list);
  std::forward_list< unsigned long long > outNumbers(std::ostream& out, FLPairs list, size_t maxLen, size_t n);
  std::ostream& outFwdListULL(std::ostream& out, std::forward_list< unsigned long long > list);
}

#endif

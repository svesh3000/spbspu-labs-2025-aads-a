#ifndef OUTPUT_LIST_HPP
#define OUTPUT_LIST_HPP

#include <istream>
#include <forward_list>

namespace gavrilova
{
  using ULL = unsigned long long;
  using FLPairs = std::forward_list< std::pair< std::string, std::forward_list< ULL > > >;
  std::ostream& outNames(std::ostream& out, FLPairs list);
  std::forward_list< ULL > outNumbers(std::ostream& out, FLPairs list, size_t maxLen, size_t n);
  std::ostream& outFwdListULL(std::ostream& out, std::forward_list< ULL > list);
}

#endif

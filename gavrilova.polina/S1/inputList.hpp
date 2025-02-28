#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <istream>
#include <forward_list>

namespace gavrilova
{
  using FLpairs = std::forward_list< std::pair< std::string, std::forward_list< unsigned long long > > >;
  std::forward_list< unsigned long long > inputNumbers(std::istream& in, size_t& curLen);
}

#endif

#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <istream>
#include <forward_list>

namespace gavrilova
{
  using FLpairs = std::forward_list< std::pair< std::string, std::forward_list< int > > >;
  std::forward_list< int > inputNumbers(std::istream& in, size_t& curLen);
}

#endif

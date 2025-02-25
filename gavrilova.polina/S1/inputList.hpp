#ifndef INPUT_LIST_HPP
#define INPUT_LIST_HPP

#include <istream>
#include <forward_list>

namespace gavrilova
{
  std::forward_list< int > inputNumbers (std::istream& in, size_t& maxLen);
}

#endif
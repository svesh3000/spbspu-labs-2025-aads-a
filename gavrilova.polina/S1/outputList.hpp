#ifndef OUTPUT_LIST_HPP
#define OUTPUT_LIST_HPP

#include <istream>
#include <forward_list>

namespace gavrilova
{
  std::ostream& outNames(std::ostream& out, std::forward_list< std::pair< std::string, std::forward_list< int > > > list);
  std::forward_list< int > outNumbers(std::ostream& out, std::forward_list< std::pair< std::string, std::forward_list< int > > > list, size_t maxLen, size_t n);
  std::ostream& outFwdListInt(std::ostream& out, std::forward_list< int > list);
}

#endif
#ifndef IO_CONTAINERS_HPP
#define IO_CONTAINERS_HPP
#include <forward_list>
#include <cstring>
#include <utility>
#include <iostream>

namespace zakirov
{
  std::pair< std::string, std::forward_list< long long int > > get_strlist_pair(std::istream & in);
  std::forward_list< long long int > get_numeric_list(std::istream & in);
  void output_result (std::ostream & out,
    std::forward_list< std::pair< std::string, std::forward_list< long long int > > > & forward_list);
}

#endif

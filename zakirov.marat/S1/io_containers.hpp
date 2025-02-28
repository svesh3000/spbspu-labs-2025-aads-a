#ifndef IO_CONTAINERS_HPP
#define IO_CONTAINERS_HPP
#include <forward_list>
#include <cstring>
#include <utility>
#include <iostream>

using pair_strlist = std::pair< std::string, std::forward_list< long long int > >;
using list_llint = std::forward_list< long long int >;
using list_pair = std::forward_list< std::pair< std::string, std::forward_list< long long int > > >;

namespace zakirov
{
  void get_list_pair(std::istream & in, list_pair & forward_list);
  void get_pair_strlist(std::istream & in, pair_strlist & forward_list);
  void get_list_llint(std::istream & in, list_llint & forward_list);
  void output_result(std::ostream & out, list_pair & forward_list);
}

#endif

#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include <cstddef>
#include <string>
#include "list.hpp"

namespace bocharov
{
  using list_t = bocharov::List< unsigned long long >;
  using pairs_list_t = bocharov::List< std::pair< std::string, list_t > >;

  std::size_t get_max_pairs_list_size(const pairs_list_t & list) noexcept;
  void get_lists_sums(list_t & sums, const pairs_list_t & pairs_list);
  void print_lists_info(std::ostream & out, const pairs_list_t & pairs_list);
}

#endif

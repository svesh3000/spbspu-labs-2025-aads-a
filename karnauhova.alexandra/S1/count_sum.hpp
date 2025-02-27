#ifndef COUNT_SUM_HPP
#define COUNT_SUM_HPP

#include <iostream>
#include <forward_list>

namespace karnauhova
{
  int element_lists(std::forward_list<unsigned long long> lists, size_t index);
  void count_lists(std::forward_list<std::pair<std::string, std::forward_list<unsigned long long>>> l, std::ostream& out);
}

#endif

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>
#include <forward_list>

namespace karnauhova
{
  void output_names_lists(std::forward_list<std::pair<std::string, std::forward_list<int>>> lists, std::ostream& out);
  void output_element_lists(std::forward_list<int> lists, size_t index, std::ostream& out, bool& first);
  void output_elements_lists(std::forward_list<std::pair<std::string, std::forward_list<int>>> lists, std::ostream& out);
}

#endif
#include "output.hpp"
void karnauhova::output_names_lists(std::forward_list<std::pair<std::string, std::forward_list<int>>> lists, std::ostream& out)
{
  auto it = lists.begin();
  out << it->first;
  it++;
  for (; it != lists.end(); it++)
  {
    out << " " << it->first;
  }
  out << "\n";
}
#include "output.hpp"

void karnauhova::output_names(std::forward_list<std::pair<std::string, std::forward_list<int>>> l, std::ostream& out)
{
  auto it = l.begin();
  if (it == l.end())
  {
    return;
  }
  out << it->first;
  it++;
  for (; it != l.end(); it++)
  {
    out << " " << it->first;
  }
  out << "\n";
}

void karnauhova::output_element_lists(std::forward_list<int> lists, size_t index, std::ostream& out, bool& first)
{
  size_t count = 1;
  auto it = lists.begin();
  while (it != lists.end() && count < index)
  {
    it++;
    count++;
  }
  if (it == lists.end())
  {
    return;
  }
  if (!first)
  {
    out << " ";
  }
  first = false;
  out << *it;
}

void karnauhova::output_lists(std::forward_list<std::pair<std::string, std::forward_list<int>>> l, std::ostream& out)
{
  int max_length = 0;
  for (const auto& it : l)
  {
    if (std::distance((it.second).begin(), (it.second).end()) > max_length)
    {
      max_length = std::distance((it.second).begin(), (it.second).end());
    }
  }
  for (int i = 0; i < max_length; ++i)
  {
    bool first = true;
    for (const auto& it : l)
    {
      output_element_lists(it.second, (i + 1), out, first);
    }
    out << "\n";
  }
}

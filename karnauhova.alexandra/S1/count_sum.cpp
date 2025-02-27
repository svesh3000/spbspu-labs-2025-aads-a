#include "count_sum.hpp"
#include <limits>

int karnauhova::element_lists(std::forward_list<unsigned long long> lists, size_t index)
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
    return 0;
  }
  return *it;
}

void karnauhova::count_lists(std::forward_list<std::pair<std::string, std::forward_list<unsigned long long>>> l, std::ostream& out)
{
  int max_length = 0;
  unsigned long long sum = 0;
  for (const auto& it : l)
  {
    if (std::distance((it.second).begin(), (it.second).end()) > max_length)
    {
      max_length = std::distance((it.second).begin(), (it.second).end());
    }
  }
  if (max_length == 0)
  {
    out << 0 << "\n";
    return;
  }
  for (int i = 0; i < max_length; ++i)
  {
    for (const auto& it : l)
    {
      unsigned long long element = element_lists(it.second, (i + 1));
      if (std::numeric_limits<unsigned long long>::max() - element < sum)
      {
        throw std::logic_error("Incorrect sum");
      }
      sum += element;
    }
    if (i != 0)
    {
      out << " ";
    }
    out << sum;
    sum = 0;
  }
  out << "\n";
}

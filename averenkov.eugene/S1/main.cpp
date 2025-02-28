#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

int main()
{
  std::string name;
  averenkov::List< std::pair< std::string, averenkov::List< unsigned long long > > > list;
  while (std::cin >> name)
  {
    std::pair< std::string, averenkov::List< unsigned long long > > sublist;
    sublist.first = name;
    unsigned long long values = 0;
    while (std::cin >> values)
    {
      sublist.second.push_back(values);
    }
    std::cin.clear();
    list.push_back(sublist);
  }

  if (list.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (auto i = list.begin(); i != list.end(); i++)
  {
    std::cout << i->first << " ";
  }
  std::cout << "\n";

  size_t max_size = 0;
  for (auto it = list.begin(); it != list.end(); it++)
  {
    if (it->second.size() > max_size)
    {
      max_size = it->second.size();
    }
  }

  averenkov::List< averenkov::List< unsigned long long > > merged;
  for (size_t i = 0; i < max_size; i++)
  {
    averenkov::List< unsigned long long > temp;
    for (auto it = list.begin(); it != list.end(); it++)
    {
      auto num_it = it->second.begin();
      for (size_t j = 0; j < i && num_it != it->second.end(); j++)
      {
        ++num_it;
      }
      if (num_it != it->second.end())
      {
        temp.push_back(*num_it);
      }
    }
    merged.push_back(temp);
  }

  for (auto it = merged.begin(); it != merged.end(); it++)
  {
    for (auto num_it = it->begin(); num_it != it->end(); num_it++)
    {
      std::cout << *num_it << " ";
    }
    std::cout << "\n";
  }

  averenkov::List<unsigned long long> sums;
  for (auto it = merged.begin(); it != merged.end(); it++)
  {
    unsigned long long sum = 0;
    for (auto num_it = it->begin(); num_it != it->end(); num_it++)
    {
      if (sum > std::numeric_limits<unsigned long long>::max() - *num_it)
      {
        std::cerr << "Error sum\n";
        return 1;
      }
      sum += *num_it;
    }
    sums.push_back(sum);
  }

  for (auto it = sums.begin(); it != sums.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  return 0;
}

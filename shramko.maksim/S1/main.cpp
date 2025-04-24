#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <limits>
#include <stdexcept>
#include "functionsForList.hpp"

namespace shramko
{
  size_t maxPairSize(const pairs_list_t& list) noexcept
  {
    size_t max = 0;
    for (const auto& pair : list)
    {
      max = std::max(max, pair.second.size());
    }
    return max;
  }

  unsigned long long getListElementSum(const list_t& list)
  {
    unsigned long long sum = 0;
    for (auto num : list)
    {
      if (sum > std::numeric_limits< unsigned long long >::max() - num)
      {
        throw std::overflow_error("Sum overflow");
      }
      sum += num;
    }
    return sum;
  }

  void printInfo(std::ostream& out, const pairs_list_t& pairs_list)
  {
    const size_t max_size = maxPairSize(pairs_list);
    list_t sum_list;

    for (size_t i = 0; i < max_size; ++i)
    {
      unsigned long long current_sum = 0;
      bool first_element = true;

      for (const auto& pair : pairs_list)
      {
        if (i < pair.second.size())
        {
          auto it = pair.second.begin();
          std::advance(it, i);

          if (!first_element)
          {
            out << " ";
          }
          out << *it;

          if (current_sum > std::numeric_limits< unsigned long long >::max() - *it)
          {
            throw std::overflow_error("Sum overflow");
          }
          current_sum += *it;
          first_element = false;
        }
      }
      out << '\n';
      sum_list.push_back(current_sum);
    }

    if (!sum_list.empty())
    {
      out << "Sums:";
      for (const auto& sum : sum_list)
      {
        out << " " << sum;
      }
      out << '\n';
    }
  }
}

int main()
{
  using namespace shramko;

  pairs_list_t pairsList;
  std::string listName;

  while (std::cin >> listName && !std::cin.eof())
  {
    list_t list;
    unsigned long long num;

    std::cin.clear();
    while (std::cin >> num)
    {
      list.push_back(num);
    }

    pairsList.emplace_back(listName, list);
    std::cin.clear();
  }

  try
  {
    if (!pairsList.empty())
    {
      auto it = pairsList.begin();
      std::cout << it->first;
      while (++it != pairsList.end())
      {
        std::cout << " " << it->first;
      }
      std::cout << '\n';
    }

    printInfo(std::cout, pairsList);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }

  return 0;
}

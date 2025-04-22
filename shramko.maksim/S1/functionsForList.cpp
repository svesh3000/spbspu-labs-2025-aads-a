#include "functionsForList.hpp"
#include <limits>
#include <stdexcept>

namespace shramko
{
  void printNames(const pairs_list_t& pairs, std::ostream& out) noexcept
  {
    if (pairs.empty())
    {
      return;
    }
    auto it = pairs.begin();
    out << it->first;
    while (++it != pairs.end())
    {
      out << " " << it->first;
    }
    out << '\n';
  }

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
      if (sum > std::numeric_limits<unsigned long long>::max() - num)
      {
        throw std::overflow_error("Sum overflow");
      }
      sum += num;
    }
    return sum;
  }

  bool isSumOverflow(size_t a, size_t b) noexcept
  {
    return a > std::numeric_limits<size_t>::max() - b;
  }

  void printSequences(const pairs_list_t& pairs, std::ostream& out)
  {
    const size_t max_size = maxPairSize(pairs);
    list_t sum_list;

    for (size_t i = 0; i < max_size; ++i)
    {
      unsigned long long current_sum = 0;
      bool first_element = true;
      
      for (const auto& pair : pairs)
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
          
          if (isSumOverflow(current_sum, *it))
          {
            throw std::overflow_error("Sum overflow in sequence");
          }
          current_sum += *it;
          first_element = false;
        }
      }
      out << '\n';
      sum_list.push_back(current_sum);
    }

    out << "Sums: ";
    for (auto it = sum_list.begin(); it != sum_list.end(); ++it)
    {
      if (it != sum_list.begin())
      {
        out << " ";
      }
      out << *it;
    }
    out << '\n';
  }
}

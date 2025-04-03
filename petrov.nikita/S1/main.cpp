#include "forward_ring_list.hpp"
#include <string>
#include "manipulations_with_fwd_ring_list.hpp"
#include <iostream>
#include <limits>

int main()
{
  petrov::ForwardRingList< std::pair< std::string, petrov::ForwardRingList< size_t > > > fwd_ring_list = {};
  petrov::inputValuesIntoFwdRingList(std::cin, fwd_ring_list);
  if (fwd_ring_list.empty())
  {
    std::cout << 0;
    std::cout << "\n";
    return 0;
  }
  petrov::outputNamesOfSuquences(std::cout, fwd_ring_list);
  petrov::ForwardRingList< size_t > sums = {};
  do
  {
    size_t sum = 0;
    auto prev_it_out = fwd_ring_list.end();
    auto it_out = fwd_ring_list.begin();
    do
    {
      if (it_out->second.empty() && fwd_ring_list.size() != 1)
      {
        auto val = *it_out;
        fwd_ring_list.remove(val);
        it_out = prev_it_out;
      }
      else if (it_out->second.empty() && fwd_ring_list.size() == 1)
      {
        fwd_ring_list.pop_front();
        break;
      }
      else
      {
        auto it = it_out->second.begin();
        if (it_out == fwd_ring_list.begin())
        {
          std::cout << *it;
          if (sum <= std::numeric_limits< size_t >::max() - *it)
          {
            sum += *it;
            it_out->second.pop_front();
          }
          else
          {
            std::cout << "\n";
            std::cerr << "ERROR: Overflow" << "\n";
            return 1;
          }
        }
        else
        {
          std::cout << " " << *it;
          if (sum <= std::numeric_limits< size_t >::max() - *it)
          {
            sum += *it;
            it_out->second.pop_front();
          }
          else
          {
            std::cout << "\n";
            std::cerr << "ERROR: Overflow" << "\n";
            return 1;
          }
        }
        ++prev_it_out;
      }
    }
    while (it_out++ != fwd_ring_list.end() && fwd_ring_list.begin() != fwd_ring_list.end());
    if (sum)
    {
      sums.push_front(sum);
      std::cout << "\n";
    }
  }
  while (!fwd_ring_list.empty());
  if (sums.empty())
  {
    std::cout << 0;
  }
  else
  {
    sums.reverse();
    if (sums.size() == 1)
    {
      std::cout << *sums.cbegin();
    }
    else
    {
      auto it = sums.cbegin();
      std::cout << *(it++);
      do
      {
        std::cout << " " << *it;
      }
      while (it++ != sums.cend());
    }
  }
  std::cout << "\n";
}

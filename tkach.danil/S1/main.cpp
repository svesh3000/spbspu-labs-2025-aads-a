#include <iostream>
#include <forward_list>
#include <string>
#include "list.hpp"

int main()
{
  using namespace tkach;
  List< std::pair< std::string, List < size_t > > > fd_pair_list;
  std::string list_name = "";
  while(std::cin >> list_name)
  {
    if (list_name.empty())
    {
      continue;
    }
    List < size_t > temp_list;
    size_t num = 0;
    while(std::cin >> num)
    {
      temp_list.push_back(num);
    }
    fd_pair_list.push_back(std::make_pair(list_name, temp_list));
    std::cin.clear();
  }
  if (fd_pair_list.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  std::cout << (fd_pair_list.begin())->first;
  for (auto it = ++fd_pair_list.begin(); it != fd_pair_list.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";
  List< size_t > sums;
  List< size_t > new_list;
  new_list.push_front(0);
  while (!new_list.empty())
  {
    new_list.clear();
    size_t sum = 0;
    auto it = fd_pair_list.begin();
    do
    {
      if (it->second.empty())
      {
        continue;
      }
      size_t pair_second_front = it->second.front();
      if (!(sum <= sum + pair_second_front && pair_second_front <= sum + pair_second_front))
      {
        throw std::overflow_error("Overflaw");
      }
      sum += pair_second_front;
      new_list.push_back(pair_second_front);
      it->second.pop_front();
      it++;
    } while(it != fd_pair_list.begin());
    if (!new_list.empty())
    {
      std::cout << new_list.front();
      for (auto it = ++new_list.begin(); it != new_list.end(); ++it)
      {
        std::cout << " " << *it;
      }
      std::cout << "\n";
      if (sum != 0)
      {
        sums.push_back(sum);
      }
    }
  }
  if (sums.empty())
  {
    std:: cout << 0 << "\n";
    return 1;
  }
  std::cout << sums.front();
  for (auto it = ++sums.begin(); it != sums.end(); ++it)
  {
    std::cout << " " << *it;
  }
  std::cout << "\n";
  return 0;
}

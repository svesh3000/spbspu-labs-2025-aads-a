#include <forward_list>
#include <string>
#include <iostream>
#include <limits>

int main()
{
  std::forward_list< std::pair< std::string, std::forward_list< size_t > > > head = {};
  std::string sequence_num = {};
  size_t number = 0;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::cin >> sequence_num;
    std::forward_list< size_t > subhead = {};
    while (!std::cin.eof() && std::cin)
    {
      std::cin >> number;
      if (!std::cin)
      {
        break;
      }
      subhead.push_front(number);
    }
    subhead.reverse();
    head.push_front({ sequence_num, subhead });
  }
  head.reverse();
  auto it = head.begin();
  std::cout << (it++)->first;
  for (; it != head.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";
  std::forward_list< size_t > sums = {};
  do
  {
    size_t sum = 0;
    auto it = head.begin();
    while (it != head.end())
    {
      if (it->second.empty())
      {
        auto temp = it._M_next();
        head.remove(*it);
        it = temp;
        if (it == head.end())
        {
          break;
        }
        continue;
      }
      else
      {
        if (it == head.begin())
        {
          if (sum <= std::numeric_limits< size_t >::max() - *it->second.begin())
          {
            std::cout << *it->second.begin();
            sum += *it->second.begin();
            it->second.pop_front();
          }
          else
          {
            std::cerr << "ERROR: Overflow" << "\n";
            return 1;
          }
        }
        else
        {
          if (sum <= std::numeric_limits< size_t >::max() - *it->second.begin())
          {
            std::cout << " " << *it->second.begin();
            sum += *it->second.begin();
            it->second.pop_front();
          }
          else
          {
            std::cerr << "ERROR: Overflow" << "\n";
            return 1;
          }
        }
      }
      ++it;
    }
    if (sum)
    {
      sums.push_front(sum);
      std::cout << "\n";
    }
  }
  while (!head.empty());
  if (sums.empty())
  {
    std::cout << 0;
  }
  else
  {
    sums.reverse();
    for (auto it = sums.begin(); it != sums.end(); ++it)
    {
      std::cout << *it << " ";
    }
  }
  std::cout << "\n";
}

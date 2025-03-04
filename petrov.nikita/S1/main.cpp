#include <iostream>
#include <forward_list>

int main()
{
  std::forward_list< std::pair< std::string, std::forward_list< int > > > head = {};
  std::string sequence_num = {};
  int number = 0;
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::cin >> sequence_num;
    std::forward_list< int > subhead = {};
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
  std::clog << "===============" << "\n";
  std::clog << "Lists' output:" << "\n";
  for (auto it = head.begin(); it != head.end(); ++it)
  {
    std::clog << it->first;
    for (auto it_in = it->second.begin(); it_in != it->second.end(); ++it_in)
    {
      std::clog << " " << *it_in;
    }
    std::clog << "\n";
  }
  std::clog << "===============" << "\n";
  auto it = head.begin();
  std::cout << (it++)->first;
  for (; it != head.end(); ++it)
  {
    std::cout << " " << it->first;
  }
  std::cout << "\n";
  std::forward_list< int > sums = {};
  do 
  {
    int sum = 0;
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
        std::cout << *it->second.begin() << " ";
        sum += *it->second.begin();
        it->second.pop_front();
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
  sums.reverse();
  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}

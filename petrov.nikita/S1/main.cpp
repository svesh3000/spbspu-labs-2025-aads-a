#include <cstring>
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
  std::cout << head.begin()->first;
  size_t count = 1;
  for (auto it = ++head.begin(); it != head.end(); ++it)
  {
    std::cout << " " << it->first;
    count++;
  }
  std::cout << "\n";
  std::forward_list< int > sums = {};
  int sum = 0;
  for (auto it = head.begin(); it != head.end(); ++it)
  {
    auto it_in = it->second.begin();
    std::cout << *it_in << " ";
    sum += *it_in;
  }
  std::cout << "\b\n";
  sums.push_front(sum);
  sums.reverse();
  std::cout << *sums.begin();
  std::cout << "\n";
}
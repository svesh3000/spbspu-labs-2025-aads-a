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
  std::cout << head.begin()->first;
  size_t count = 1;
  for (auto it = ++head.begin(); it != head.end(); ++it)
  {
    std::cout << " " << it->first;
    count++;
  }
  std::cout << "\n";
  std::forward_list< int > sums = {};
  for (size_t i = 0; i < count; i++)
  {
    int sum = 0;
    for (auto it = head.begin(); it != head.end(); ++it)
    {
      auto it_in = it->second.begin();
      for (size_t j = 0; j < i; j++)
      {
        ++it_in;
      }
      std::cout << *it_in << " ";
      sum += *it_in;
    }
    sums.push_front(sum);
    std::cout << "\b\n";
  }
  sums.reverse();
  std::cout << *sums.begin();
  for (auto it = ++sums.begin(); it != sums.end(); ++it)
  {
    std::cout << " " << *it;
  }
  std::cout << "\n";
}
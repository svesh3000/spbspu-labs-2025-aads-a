#include <iostream>
#include <forward_list>
#include <string>
#include "list.hpp"

int main()
{
  maslov::List< std::pair< std::string, std::forward_list< int > > > pair;
  std::string name;
  int number = 0;
  while (std::cin >> name && !std::cin.eof())
  {
    std::forward_list<int> numbers;
    while (std::cin >> number)
    {
      numbers.push_front(number);
    }
    pair.push_back(std::make_pair(name, numbers));
  }
}

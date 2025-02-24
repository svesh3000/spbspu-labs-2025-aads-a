#include <iostream>
#include <string>
#include <forward_list>
#include "list.hpp"
#include "listUtils.hpp"

int main()
{
  std::forward_list< std::pair< std::string, std::forward_list< int > > > listOfPairs;
  std::string name;
  int number = 0;
  size_t maxSize = 0;
  auto it = listOfPairs.before_begin();
  while (std::cin >> name && !std::cin.eof())
  {
    size_t size = 0;
    std::forward_list<int> numbers;
    auto itNum = numbers.before_begin();
    while (std::cin >> number)
    {
      itNum = numbers.insert_after(itNum, number);
      size++;
    }
    maxSize = std::max(maxSize, size);
    it = listOfPairs.insert_after(it, std::make_pair(name, numbers));
    std::cin.clear();
  }
  maslov::print(std::cout, listOfPairs, maxSize);
  std::cout << "\n";
}

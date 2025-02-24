#include <iostream>
#include <string>
#include <forward_list>
#include "list.hpp"
#include "listUtils.hpp"

int main()
{
  std::forward_list< std::pair< std::string, std::forward_list< size_t > > > listOfPairs;
  std::string name;
  size_t number = 0;
  size_t maxSize = 0;
  auto it = listOfPairs.before_begin();
  while (std::cin >> name && !std::cin.eof())
  {
    size_t size = 0;
    std::forward_list< size_t > numbers;
    auto itNum = numbers.before_begin();
    while (std::cin >> number && !std::cin.eof())
    {
      itNum = numbers.insert_after(itNum, number);
      size++;
    }
    maxSize = std::max(maxSize, size);
    it = listOfPairs.insert_after(it, std::make_pair(name, numbers));
    std::cin.clear();
  }
  if (listOfPairs.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  try
  {
    maslov::printData(std::cout, listOfPairs, maxSize);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  std::cout << "\n";
}

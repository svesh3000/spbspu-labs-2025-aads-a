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
  while (std::cin >> name && !std::cin.eof())
  {
    size_t size = 0;
    std::forward_list< size_t > numbers;
    while (std::cin >> number && !std::cin.eof())
    {
      numbers.push_front(number);
      size++;
    }
    numbers.reverse();
    maxSize = std::max(maxSize, size);
    listOfPairs.push_front(std::make_pair(name, numbers));
    std::cin.clear();
  }
  listOfPairs.reverse();
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

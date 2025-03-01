#include <iostream>
#include <list>
#include <string>
#include "list.hpp"

int main()
{
  using namespace smirnov;
  std::list< std::pair< std::string, List< size_t > > > sequences;
  std::string input;
  std::string name;
  List< size_t > list;
  while (std::cin >> input)
  {
    if (isdigit(input[0]))
    {
      int number = std::stoi(input);
      list.pushBack(number);
    }
    else
    {
      if (!name.empty())
      {
        sequences.emplace_back(name, list);
        list = List< size_t >();
      }
      name = input;
    }
  }
}

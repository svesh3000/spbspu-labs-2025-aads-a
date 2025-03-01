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

  if (!name.empty())
  {
    sequences.emplace_back(name, list);
  }

  if (sequences.empty())
  {
    std::cout << 0 << std::endl;
    return 0;
  }

  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    const std::pair< std::string, List< size_t > > & sequence = *it;
    if (it != sequences.begin())
    {
     std::cout << " ";
    }
    std::cout << sequence.first;
  }
  if (!sequences.empty())
  {
    std::cout << "\n";
  }
}

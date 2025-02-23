#include "input.hpp"
#include <iostream>

int main()
{
  std::string name = "kekw";
  std::forward_list<std::pair<std::string, std::forward_list<int>>> lists{};
  while (std::cin >> name && !std::cin.eof())
  {
    lists.push_front(karnauhova::input_line(std::cin, name));
  }
  lists.reverse();
  for (const auto& it : lists)
  {
    std::cout << it.first << " ";
    for (const int& num : it.second) 
    {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

}

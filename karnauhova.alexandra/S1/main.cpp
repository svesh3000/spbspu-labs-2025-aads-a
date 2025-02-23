#include <iostream>
#include "output.hpp"
#include "input.hpp"

int main()
{
  std::string name = "kekw";
  std::forward_list<std::pair<std::string, std::forward_list<int>>> lists{};
  while (std::cin >> name && !std::cin.eof())
  {
    lists.push_front(karnauhova::input_line(std::cin, name));
  }
  lists.reverse();
  karnauhova::output_names_lists(lists, std::cout);
  for (const auto& it : lists)
  {
    for (const int& num : it.second) 
    {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

}

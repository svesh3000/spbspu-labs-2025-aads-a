#include "input.hpp"
#include <iostream>
#include <string>

std::pair<std::string, std::forward_list<int>> karnauhova::input_line(std::istream& in, std::string name)
{
  int x = 0;
  std::forward_list<int> numbers{};
  while (in >> x && !in.eof())
  {
        numbers.push_front(x);
  }
  in.clear();
  numbers.reverse();
  std::pair<std::string, std::forward_list<int>> p (name, numbers);
  return p;
}

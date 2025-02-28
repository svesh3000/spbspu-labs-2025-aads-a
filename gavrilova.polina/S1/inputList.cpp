#include "inputList.hpp"

std::forward_list< unsigned long long > gavrilova::inputNumbers (std::istream& in, size_t& curLen)
{
  std::forward_list< unsigned long long > numbers;
  unsigned long long num = 0;
  curLen = 0;
  while (in >> num && !in.eof()) {
    numbers.push_front(num);
    ++curLen;
  }
  in.clear();
  numbers.reverse();
  return numbers;
}


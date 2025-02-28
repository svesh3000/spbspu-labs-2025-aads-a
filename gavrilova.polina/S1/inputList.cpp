#include "inputList.hpp"
#include <string>

std::forward_list< int > gavrilova::inputNumbers (std::istream& in, size_t& curLen)
{
  std::forward_list< int > numbers;
  int num = 0;
  curLen = 0;
  while (in >> num && !in.eof()) {
    numbers.push_front(num);
    ++curLen;
  }
  in.clear();
  numbers.reverse();
  return numbers;
}

gavrilova::FLpairs& gavrilova::inputList (std::istream& in, FLpairs& list, size_t& maxLen, size_t& num)
{
  std::string name;
  size_t curLen = 0;
  while (in >> name && !in.eof()) {
    std::forward_list< int > numbers = inputNumbers(in, curLen);
    maxLen = (maxLen < curLen) ? curLen : maxLen;
    if (curLen) {
      list.push_front({name, numbers});
      ++num;
    }
  }
  return list;
}

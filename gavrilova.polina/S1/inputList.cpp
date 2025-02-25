#include "inputList.hpp"

std::forward_list< int > gavrilova::inputNumbers (std::istream& in, size_t& maxLen) {
  std::forward_list< int > numbers;
  int num = 0;
  size_t len = 0;
  while (in >> num && !in.eof()) {
    numbers.push_front(num);
    ++len;
  }
  maxLen = (maxLen < len) ? len : maxLen;
  in.clear();
  numbers.reverse;
  return numbers;
}
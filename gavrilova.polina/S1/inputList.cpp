#include "inputList.hpp"

std::forward_list< int > gavrilova::inputNumbers (std::istream& in, size_t& curLen) {
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
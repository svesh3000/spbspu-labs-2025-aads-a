#include "inputList.hpp"

gavrilova::FwdList< unsigned long long > gavrilova::inputNumbers(std::istream& in)
{
  FwdList< unsigned long long > numbers;
  unsigned long long num = 0;
  auto it = numbers.cbegin();
  // std::cout << "start input numbers\n";
  while (in >> num) {
    // std::cout << "+num\n";
    numbers.insert(it, num);
    ++it;
  }
  in.clear();
  return numbers;
}

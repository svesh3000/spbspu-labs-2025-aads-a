#include <iostream>
#include <sstream>
#include <utility>

#include "CircularFwdList.hpp"

int main()
{
  using IntList = zholobov::CircularFwdList< unsigned int >;
  using ListElem = std::pair< std::string, IntList >;
  zholobov::CircularFwdList< ListElem > list;
  while (!std::cin.eof()) {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::string name;
    IntList int_list;
    ss >> name;
    while (ss) {
      int elem = 0;
      if (ss >> elem) {
        int_list.push_back(elem);
      }
    }
    ListElem list_elem(std::move(name), std::move(int_list));
    list.push_back(std::move(list_elem));
  }

  zholobov::CircularFwdList< std::pair< IntList::iterator, IntList::iterator > > iter_list;
  for (auto it = list.begin(); it != list.end(); ++it) {
    std::cout << it->first << " ";
    iter_list.push_back(std::pair< IntList::iterator, IntList::iterator >(it->second.begin(), it->second.end()));
  }
  std::cout << "\n";

  zholobov::CircularFwdList< unsigned int > sum_list;
  bool is_done_printing = true;
  do {
    is_done_printing = true;
    unsigned int sum = 0;
    for (auto it = iter_list.begin(); it != iter_list.end(); ++it) {
      if (it->first != it->second) {
        unsigned int val = *(it->first);
        std::cout << val << " ";
        ++it->first;
        is_done_printing = false;
        sum += val;
      }
    }
    if (!is_done_printing) {
      std::cout << "\n";
      sum_list.push_back(sum);
    }
  } while (!is_done_printing);

  for (auto it = sum_list.begin(); it != sum_list.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\n";

  return 0;
}

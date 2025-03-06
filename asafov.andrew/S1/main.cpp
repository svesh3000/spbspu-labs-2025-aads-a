#include "fwdlst4d.hpp"
#include <iostream>

int main()
{
  asafov::Forward_list<int> list;
  std::cout << '\n' << list.size();
  list.push_back(1);
  std::cout << '\n' << list.size();
  list.push_back(2);
  std::cout << '\n' << list.size();
  list.push_back(3);
  std::cout << '\n' << list.size();
  std::cout <<std::endl;


  for (int data : list) std::cout << data << ' ';
  list.clear();
  std::cout << '\n' << list.size();

  std::cout <<std::endl;
  return 0;
}

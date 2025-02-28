#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include "actionsWithList.hpp"

int main()
{
  std::list< std::pair<std::string, std::list<size_t>>> List;
  std::string str = "";
  std::cin >> str;
  if (!std::cin.good())
  {
    std::cout << 0 << "\n";
    return 0;
  }
  std::string temp = str;
  while (true)
  {
    str = temp;
    std::list< size_t > list;
    std::string in = "";
    while (std::cin >> in)
    {
      if (std::isdigit(in[0]))
      {
        size_t num = strtoull(in.c_str(), nullptr, 10);
        list.push_back(num);
      }
      else
      {
        temp = in;
        break;
      }
    }
    List.push_back({ str, list });
    if (std::cin.eof())
    {
      break;
    }
  }
  if (List.size() == 0)
  {
    std::cout << 0 << "\n";
    return 0;
  }
  std::list<std::string> listOfHeads;
  for (auto i = List.begin(); i != List.end(); ++i)
  {
    listOfHeads.push_back((*i).first);
  }
  std::list<std::list<size_t>> listOfLists = finaev::createRightList(List);
  finaev::printList(listOfHeads, std::cout);
  for (auto i = listOfLists.begin(); i != listOfLists.end(); ++i)
  {
    finaev::printList(*i, std::cout);
  }
  if (finaev::isOverflow(listOfLists))
  {
    std::cerr << "is overflow!\n";
    return 1;
  }
  std::list<size_t> listOfSum = finaev::createListOfSum(listOfLists);
  finaev::printList(listOfSum, std::cout);
}

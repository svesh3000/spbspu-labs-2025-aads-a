#include <iostream>
#include <string>
#include <forward_list>
#include <utility>

int main()
{
  std::forward_list< std::pair< std::string, std::forward_list < int > > > list;
  std::string listName;
  auto listIter = list.before_begin();
  while (std::cin >> listName)
  {
    std::forward_list< int > numList;
    auto numListIter = numList.before_begin();
    int num = 0;
    while (std::cin >> num)
    {
      numList.insert_after(numListIter, num);
      ++numListIter;
    }
    std::cin.clear();
    list.insert_after(listIter, std::make_pair(listName, numList));
    ++listIter;
  }

  for (auto it = list.begin(); it != list.end(); ++it)
  {
    std::cout << it->first << "\n";
    for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
    {
      std::cout << *it2 << "\n";
    }
  }
}


#include <iostream>
#include <string>
#include <list>
#include <cctype>

void printList(std::list<unsigned int> list)
{
  std::cout << *list.begin();
  for (auto i = ++list.begin(); i != list.end(); ++i)
  {
    std::cout << " " <<  * i;
  }
  std::cout << "\n";
}

void printList(std::list<std::string> list)
{
  std::cout << *list.begin();
  for (auto i = ++list.begin(); i != list.end(); ++i)
  {
    std::cout << " " << *i;
  }
  std::cout << "\n";
}

int main()
{
  std::list< std::pair<std::string, std::list<unsigned int>>> List;
  bool isOverflow = 0;
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
    std::list< unsigned int > list;
    std::string in = "";
    while (std::cin >> in)
    {
      try
      {
        unsigned int num = std::stoul(in, nullptr, 10);
        std::string s = std::to_string(num);
        if (s != in)
        {
          isOverflow = true;
        }
        list.push_back(num);
      }
      catch (const std::invalid_argument&)
      {
        temp = in;
        break;
      }
    }
    std::pair<std::string, std::list<unsigned int>> pair(str, list);
    List.push_back(pair);
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
  std::list<std::list<unsigned int>> listOfLists;
  size_t max_size = 0;
  for (auto i = List.begin(); i != List.end(); ++i)
  {
    if ((*i).second.size() > max_size)
    {
      max_size = (*i).second.size();
    }
  }
  for (size_t i = 0; i < max_size; ++i)
  {
    std::list<unsigned int> list;
    listOfLists.push_back(list);
  }
  for (auto i = List.begin(); i != List.end(); ++i)
  {
    listOfHeads.push_back((*i).first);
    auto counter = listOfLists.begin();
    for (auto j = (*i).second.begin(); j != (*i).second.end(); ++j)
    {
      (*counter).push_back(*j);
      if (counter != listOfLists.end())
      {
        ++counter;
      }
    }
  }
  std::list<unsigned int> listOfSum;
  for (auto i = listOfLists.begin(); i != listOfLists.end(); ++i)
  {
    int res = 0;
    for (auto j = (*i).begin(); j != (*i).end(); ++j)
    {
      res += *j;
    }
    listOfSum.push_back(res);
  }
  printList(listOfHeads);
  for (auto i = listOfLists.begin(); i != listOfLists.end(); ++i)
  {
    printList(*i);
  }
  if (isOverflow)
  {
    std::cerr << "is overflow!\n";
    return 1;
  }
  printList(listOfSum);
}

#include <iostream>
#include <utility>
#include <list>
#include <iomanip>

void printSequencesName(const std::list<std::pair<std::string, std::list<int>>> temporary)
{
  auto it = temporary.begin();
  std::cout << (*it).first;
  for (++it; it != temporary.end(); it++)
  {
    std::cout << " " << (*it).first;
  }
  std::cout << '\n';
}

void printSequences(const std::list < std::pair < std::string, std::list<int>>> temporary, size_t maxSize)
{
  std::list<int> sumList{};
  for (size_t i = 0; i < maxSize; i++)
  {
    size_t res = 0;
    bool isFirstElement = true;
    for (const auto& pair : temporary)
    {
      if (!pair.second.empty() && i < pair.second.size())
      {
        auto it = pair.second.begin();
        std::advance(it, i);
        if (!isFirstElement)
        {
          std::cout << " ";
        }
        std::cout << (*it);
        res += *(it);
        isFirstElement = false;
      }
    }
    sumList.push_back(res);
    std::cout << '\n';
  }
  auto it = sumList.begin();
  std::cout << (*it);
  for (++it; it != sumList.end(); it++)
  {
    std::cout << " " << (*it);
  }
  std::cout << '\n';
}

int main()
{
  std::list < std::pair<std::string, std::list<int>>> myList;
  std::string sequenceName = "";
  while (std::cin >> sequenceName)
  {
    int element = 0;
    std::list<int> temporaryList{};
    while (std::cin >> element)
    {
      temporaryList.push_back(element);
    }
    std::pair<std::string, std::list<int>> temporaryPair{ sequenceName, temporaryList };
    myList.push_back(temporaryPair);
    if (std::cin.eof())
    {
      break;
    }
    std::cin.clear();
  }
  printSequencesName(myList);
  size_t maxSize = 0;
  for (auto it :myList)
  {
    if (maxSize < it.second.size())
    {
      maxSize = it.second.size();
    }
  }
  printSequences(myList, maxSize);
}

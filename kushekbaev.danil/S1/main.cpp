#include <iostream>
#include <list>
#include <utility>

using pairedList = std::list< std::pair<std::string, std::list< int > > >;

int main()
{
  std::list< std::pair< std::string, std::list< int > > > pairsList;
  std::string nodeName = "";
  std::list< std::string > nodeList;
  std::list< int > valueList;
  std::list< int > sumList;

  while (!std::cin.eof())
  {
    while (std::cin >> nodeName)
    {
      std::list< int > valueList;
      int value = 0;
      while (std::cin >> value)
      {
        valueList.push_back(value);
      }
      pairsList.push_back(std::make_pair(nodeName, valueList));
      std::cin.clear();
    }

    if (pairsList.size() == 0)
    {
      std::cout << "0\n";
      return 0;
    }

    std::cout << pairsList.begin()->first;
    for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
    {
      std::cout << " " << it->first;
    }
    std::cout << "\n";

    size_t max_size = 0;

    for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
    {
      max_size = std::max(max_size, it->second.size());
    }

    for (size_t i = 0; i < max_size; ++i)
    {
      std::list< int > valueList;
      for (auto it = ++pairsList.begin(); it != pairsList.end(); ++it)
      {
        if (!it->second.empty())
        {
          valueList.push_back(it->second.front());
          it->second.pop_front();
        }
      }

      if (!valueList.empty())
      {
        std::cout << valueList.front();
        for (auto it = ++valueList.begin(); it != valueList.end(); ++it)
        {
          std::cout << " " << *it;
        }
        std::cout << "\n";
        int sum = 0;
        for (auto it = ++valueList.begin(); it != valueList.end(); ++it)
        {
          sum += *it;
        }
        valueList.push_back(sum);
      }
    }

    std::cout << sumList.front();
    for (auto it = ++valueList.begin(); it != valueList.end(); ++it)
    {
      std::cout << " " << *it;
    }
  }
}

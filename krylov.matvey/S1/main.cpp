#include <iostream>
#include <list>
#include <string>
#include <limits>

int main()
{
  std::list< std::pair< std::string, std::list< int > > > listOfPairs;
  std::string line = "";
  std::cin >> line;
  size_t maxSizeOfNumList = 0;
  constexpr unsigned long long maxValue = std::numeric_limits< unsigned long long >::max();
  while (!std::cin.eof())
  {
    std::pair< std::string, std::list< int > > pair;
    pair.first = line;
    std::cin >> line;
    while (!std::cin.eof() && isdigit(line[0]))
    {
      unsigned long long currentValue = strtoull(line.c_str(), nullptr, 0);
      if (currentValue >= maxValue)
      {
        std::cerr << "Overflow\n";
        return 1;
      }
      pair.second.push_back(currentValue);
      std::cin >> line;
    }
    if (maxSizeOfNumList < pair.second.size())
    {
      maxSizeOfNumList = pair.second.size();
    }
    listOfPairs.push_back(pair);
  }
  if (listOfPairs.empty())
  {
    std::cout << "0\n";
    return 0;
  }

  for (auto it = listOfPairs.begin(); it != --listOfPairs.end(); ++it)
  {
    std::cout << it->first << " ";
  }
  std::cout << (--listOfPairs.end())->first << "\n";

  std::list< int > listOfLineSums;
  for (size_t i = 0; i < maxSizeOfNumList; ++i)
  {
    int sumOfLine = 0;
    for (auto it = listOfPairs.begin(); it != listOfPairs.end(); ++it)
    {
      if (it->second.size() <= i)
      {
        continue;
      }
      auto currentValue = std::next(it->second.begin(), i);
      sumOfLine += *currentValue;
    }
    listOfLineSums.push_back(sumOfLine);
  }

  for (size_t i = 0; i < maxSizeOfNumList; ++i)
  {
    bool isSpaceAvailable = false;
    for (auto it = listOfPairs.begin(); it != --(listOfPairs.end()); ++it)
    {
      if (it->second.size() > i)
      {
        if (isSpaceAvailable)
        {
          std::cout << " ";
        }
        auto current = std::next(it->second.begin(), i);
        std::cout << *current;
        isSpaceAvailable = true;
      }
    }
    if ((--listOfPairs.end())->second.size() <= i)
    {
      std::cout << "\n";
      continue;
    }
    std::cout << " " << *(std::next((--(listOfPairs.end()))->second.begin(), i)) << "\n";
  }

  for (auto it = listOfLineSums.begin(); it != --listOfLineSums.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << *(--listOfLineSums.end()) << "\n";
}


#include <iostream>
#include <list>
#include <string>

int main()
{
  std::list< std::pair< std::string, std::list< int > > > listOfPairs;
  std::string line = "";
  std::cin >> line;
  size_t maxSizeOfNumList = 0;
  while (!std::cin.eof())
  {
    std::pair< std::string, std::list< int > > pair;
    pair.first = line;
    std::cin >> line;
    while (!std::cin.eof() && isdigit(line[0]))
    {
      pair.second.push_back(strtoull(line.c_str(), nullptr, 0));
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
    for (auto it = listOfPairs.begin(); it != --(listOfPairs.end()); ++it)
    {
      if (it->second.size() <= i)
      {
        continue;
      }
      auto current = std::next(it->second.begin(), i);
      std::cout << *current << " ";
    }
    if ((--listOfPairs.end())->second.size() <= i)
    {
      std::cout << "\n";
      continue;
    }
    std::cout << *(std::next((--(listOfPairs.end()))->second.begin(), i)) << "\n";
  }

  for (auto it = listOfLineSums.begin(); it != --listOfLineSums.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << *(--listOfLineSums.end()) << "\n";
}


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

  std::list< int > listOfLineSums;
  for (auto it = listOfPairs.begin(); it != listOfPairs.end(); ++it)
  {
    int sumOfLine = 0;
    for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
    {
      sumOfLine += *iter;
    }
    listOfLineSums.push_back(sumOfLine);
  }
  for (auto it = listOfPairs.begin(); it != --listOfPairs.end(); ++it)
  {
    std::cout << it->first << " ";
  }
  std::cout << (--listOfPairs.end())->first << "\n";


  for (size_t i = 0; i < maxSizeOfNumList; i++)
  {
    for (auto it = listOfPairs.begin(); it != --(listOfPairs.end()); ++it)
    {
      auto current = std::next(it->second.begin(), i);
      std::cout << *current << " ";
    }
    std::cout << *(std::next((--(listOfPairs.end()))->second.begin(), i)) << "\n";
  }

  for (auto it = listOfLineSums.begin(); it != --listOfLineSums.end(); ++it)
  {
    std::cout << *it << " ";
  }
  std::cout << *(--listOfLineSums.end()) << "\n";
}


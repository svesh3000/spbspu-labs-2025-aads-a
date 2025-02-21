#include <iostream>
#include <utility>
#include <list>
#include <string>

int main()
{
  std::list< std::pair< std::string, std::list< int > > > listOfPairs;
  std::string line = "";
  std::cin >> line;
  while (!std::cin.eof())
  {
    std::pair< std::string, std::list< int > > pair;
    pair.first = line;
    std::cin >> line;
    while (!std::cin.eof() && isdigit(line[0]))
    {
      pair.second.push_back(line[0]);
      std::cin >> line;
    }
    listOfPairs.push_back(pair);
  }
}

#include <iostream>
#include <string>
#include "list.hpp"

int main()
{
  rychkov::List< std::pair< std::string, rychkov::List< int > > > entered;
  std::string name;
  while (std::cin >> name)
  {
    entered.push_back({name, {}});
    int number = 0;
    while (std::cin >> number)
    {
      entered.back().second.push_back(number);
    }
    std::cin.clear();
  }

  char space[2] = "\0";
  for (const std::pair< std::string, rychkov::List< int > >& i : entered)
  {
    std::cout << space << i.first;
    space[0] = ' ';
  }
  std::cout << '\n';

  rychkov::List< rychkov::List< int > > result;
  for (const std::pair< std::string, rychkov::List< int > >& i : entered)
  {
    decltype(result)::iterator wPoint = result.begin();
    for (int j : i.second)
    {
      if (wPoint != result.end())
      {
        (*wPoint).push_back(j);
        ++wPoint;
      }
      else
      {
        result.push_back({j});
      }
    }
  }

  rychkov::List< long long > sums;
  for (rychkov::List< int > i : result)
  {
    sums.push_back(0);
    space[0] = '\0';
    for (int j : i)
    {
      sums.back() += j;
      std::cout << space << j;
      space[0] = ' ';
    }
    std::cout << '\n';
  }
  space[0] = '\0';
  for (decltype(sums)::value_type i : sums)
  {
    std::cout << space << i;
    space[0] = ' ';
  }
  std::cout << '\n';
}

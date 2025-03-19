#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <cstddef>
#include "list.hpp"

int main()
{
  using namespace smirnov;
  List< std::pair< std::string, List< size_t > > > sequences;
  std::string input;
  std::string name;
  List< size_t > list;
  while (std::cin >> input)
  {
    bool isNumber = true;
    for (size_t i = 0; i < input.length(); ++i)
    {
      char c = input[i];
      if (!std::isdigit(c))
      {
        isNumber = false;
        break;
      }
    }

    if (isNumber)
    {
      try
      {
        size_t number = std::stoull(input);
        list.push_back(number);
      }
      catch (const std::out_of_range & e)
      {
        std::cerr << "Number is too large\n";
        return 1;
      }
    }
    else
    {
      if (!name.empty())
      {
        sequences.push_back(std::make_pair(name, list));
        list.clear();
      }
      name = input;
    }
  }

  if (!name.empty())
  {
    sequences.push_back(std::make_pair(name, list));
  }

  if (sequences.empty())
  {
    std::cout << 0 << "\n";
    return 0;
  }

  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    if (it != sequences.begin())
    {
      std::cout << " ";
    }
    std::cout << it->first;
  }
  std::cout << "\n";

  bool hasNum = false;
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    if (!it->second.empty())
    {
      hasNum = true;
      break;
    }
  }

  if (!hasNum)
  {
    std::cout << 0 << std::endl;
    return 0;
  }

  List< List< size_t > > resultSequences;
  bool hasNumbers = true;
  while (hasNumbers)
  {
    hasNumbers = false;
    List< size_t > resultSequence;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      if (!it->second.empty())
      {
        resultSequence.push_back(it->second.front());
        it->second.pop_front();
        hasNumbers = true;
      }
    }
    if (!resultSequence.empty())
    {
      resultSequences.push_back(resultSequence);
    }
  }

  for (auto it = resultSequences.begin(); it != resultSequences.end(); ++it)
  {
    for (auto numIt = it->begin(); numIt != it->end(); ++numIt)
    {
      if (numIt != it->begin())
      {
        std::cout << " ";
      }
      std::cout << *numIt;
    }
    std::cout << "\n";
  }

  List< size_t > sums;
  for (auto it = resultSequences.begin(); it != resultSequences.end(); ++it)
  {
    size_t sum = 0;
    for (auto numIt = it->begin(); numIt != it->end(); ++numIt)
    {
      if (sum > std::numeric_limits< size_t >::max() - *numIt)
      {
        std::cerr << "Overflow\n";
        return 1;
      }
      sum += *numIt;
    }
    sums.push_back(sum);
  }

  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    if (it != sums.begin())
    {
      std::cout << " ";
    }
    std::cout << *it;
  }
  std::cout << "\n";
}

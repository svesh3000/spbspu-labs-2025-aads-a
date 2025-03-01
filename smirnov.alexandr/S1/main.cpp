#include <iostream>
#include <list>
#include <string>
#include "list.hpp"

int main()
{
  using namespace smirnov;
  std::list< std::pair< std::string, List< size_t > > > sequences;
  std::string input;
  std::string name;
  List< size_t > list;
  while (std::cin >> input)
  {
    if (isdigit(input[0]))
    {
      int number = std::stoi(input);
      list.pushBack(number);
    }
    else
    {
      if (!name.empty())
      {
        sequences.emplace_back(name, list);
        list = List< size_t >();
      }
      name = input;
    }
  }

  if (!name.empty())
  {
    sequences.emplace_back(name, list);
  }

  if (sequences.empty())
  {
    std::cout << 0 << std::endl;
    return 0;
  }

  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    const std::pair< std::string, List< size_t > > & sequence = *it;
    if (it != sequences.begin())
    {
     std::cout << " ";
    }
    std::cout << sequence.first;
  }
  std::cout << "\n";

  std::list< List< size_t > > resultSequences;
  bool hasNumbers = true;
  while (hasNumbers)
  {
    List< size_t > currentSequence;
    hasNumbers = false;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      std::pair< std::string, List< size_t > > & seq = *it;
      if (!seq.second.isEmpty())
      {
        currentSequence.pushBack(*seq.second.begin());
        seq.second.popFront();
        hasNumbers = true;
      }
    }
    if (!currentSequence.isEmpty())
    {
      resultSequences.push_back(currentSequence);
    }
  }

  for (auto it = resultSequences.begin(); it != resultSequences.end(); ++it)
  {
    const List< size_t > & sequence = *it;
    for (auto numIt = sequence.begin(); numIt != sequence.end(); ++numIt)
    {
      if (numIt != sequence.begin())
      {
        std::cout << " ";
      }
      std::cout << *numIt;
    }
    std::cout << "\n";
  }
}

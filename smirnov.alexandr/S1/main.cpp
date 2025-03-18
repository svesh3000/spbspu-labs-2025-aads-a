#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

int main()
{
  using namespace smirnov;
  List< std::pair< std::string, List< unsigned long long > > > sequences;
  std::string input;
  std::string name;
  List< unsigned long long > list;
  while (std::cin >> input)
  {
    if (isdigit(input[0]))
    {
      try
      {
        unsigned long long number = std::stoull(input);
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
    std::cout << 0 << std::endl;
    return 0;
  }

  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    const std::pair< std::string, List< unsigned long long > > & sequence = *it;
    if (it != sequences.begin())
    {
      std::cout << " ";
    }
    std::cout << sequence.first;
  }
  std::cout << "\n";

  bool hasNum = false;
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    const std::pair< std::string, List< unsigned long long > > & seq = *it;
    if (!seq.second.empty())
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

  List< List< unsigned long long > > resultSequences;
  bool hasNumbers = true;
  while (hasNumbers)
  {
    List< unsigned long long > currentSequence;
    hasNumbers = false;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      const std::pair< std::string, List< unsigned long long > > & seq = *it;
      if (!seq.second.empty())
      {
        currentSequence.push_back(*seq.second.begin());
        seq.second.pop_front();
        hasNumbers = true;
      }
    }
    if (!currentSequence.empty())
    {
      resultSequences.push_back(currentSequence);
    }
  }

  for (auto it = resultSequences.begin(); it != resultSequences.end(); ++it)
  {
    const List< unsigned long long > & sequence = *it;
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

  List< unsigned long long > sums;
  for (auto it = resultSequences.begin(); it != resultSequences.end(); ++it)
  {
    const List< unsigned long long > & sequence = *it;
    unsigned long long sum = 0;
    for (auto numIt = sequence.begin(); numIt != sequence.end(); ++numIt)
    {
      if (sum > std::numeric_limits< unsigned long long >::max() - *numIt)
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

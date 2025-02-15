#include <exception>
#include <iostream>
#include <limits>
#include <list>
#include <ostream>
#include <stdexcept>
#include <string>

using numberList = std::list< int >;
using pair = std::pair< std::string, numberList >;
using pairList = std::list< pair >;
std::istream& listOfNumbers(std::istream& input, numberList& listNumber)
{
  int number = 0;
  while (input >> number)
  {
    listNumber.push_back(number);
  }
  return input;
}
std::ostream& outputName(std::ostream& output, pairList& list)
{
  pairList::const_iterator end = list.end();
  for (pairList::iterator it = list.begin(); it != end; ++it)
  {
    output << it->first;
    if (std::next(it) != end)
    {
      output << " ";
    }
  }
  return output;
}

std::list< int > outputNumbers(std::ostream& output, pairList& list)
{
  pairList::const_iterator end = list.cend();
  pairList::const_iterator begin = list.cbegin();
  size_t maxCount = 0;
  for (; begin != end; ++begin)
  {
    maxCount = maxCount < begin->second.size() ? begin->second.size() : maxCount;
  }
  std::list< int > sum;
  for (size_t i = 0; i < maxCount; ++i)
  {
    int summa = 0;
    begin = list.cbegin();
    for (; begin != end; ++begin)
    {
      numberList::const_iterator nbegin = begin->second.begin();
      if (i >= begin->second.size())
      {
        continue;
      }
      std::advance(nbegin, i); //Сделать у итератора метод +=
      output << *nbegin;
      if (std::next(begin) != end)
      {
        output << " ";
      }
      summa += *nbegin;
    }
    output << "\n";
    sum.push_back(summa);
  }
  return sum;
}
std::ostream& outputSum(std::ostream& output, std::list< int >& list)
{
  std::list< int >::const_iterator begin = list.cbegin();
  for (; begin != list.cend(); ++begin)
  {
    output << *begin;
    if (std::next(begin) != list.cend())
    {
      output << " ";
    }
  }
  return output;
}

int main()
{
  pairList list;
  std::string nameNode;
  try
  {
    while (std::cin >> nameNode)
    {
      numberList numbers;
      if (!(listOfNumbers(std::cin, numbers)))
      {
        std::cerr << "Was overflow\n";
        return 1;
      }
      list.push_back(pair(nameNode, numbers));
    }
    outputName(std::cout, list) << "\n";
    if (list.empty() || list.front().second.empty())
    {
      std::cout << "0\n";
      return 0;
    }
    std::list< int > sum = outputNumbers(std::cout, list);
    outputSum(std::cout, sum) << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

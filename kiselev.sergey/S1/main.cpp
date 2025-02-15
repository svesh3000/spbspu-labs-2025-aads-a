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
void listOfNumbers(std::istream& input, numberList& listNumber)
{
  int number = 0;
  int maxInt = std::numeric_limits< int >::max();
  while (input >> number)
  {
    if (number > maxInt)
    {
      throw std::overflow_error("Overflow");
    }
    listNumber.push_back(number);
  }
  if (listNumber.empty())
  {
    listNumber.push_back(number);
  }
  input.clear();
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
      listOfNumbers(std::cin, numbers);
      list.push_back(pair(nameNode, numbers));
    }
    if (list.empty())
    {
      throw std::logic_error("There was no input");
    }
    outputName(std::cout, list) << "\n";
    std::list< int > sum = outputNumbers(std::cout, list);
    outputSum(std::cout, sum) << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}

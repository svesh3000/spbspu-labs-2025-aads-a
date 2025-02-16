#include "workFlows.hpp"
#include <cstddef>
#include <iterator>
#include <limits>
#include <ostream>
#include <stdexcept>

namespace
{
  size_t searchMax(const list& list_)
  {
    size_t max = 0;
    for (list::const_iterator begin = list_.begin(); begin != list_.end(); ++begin)
    {
      max = std::max(max, begin->second.size());
    }
    return max;
  }

  std::ostream& outputName(std::ostream& output, const list& list_)
  {
    list::const_iterator end = list_.cend();
    for (list::const_iterator it = list_.begin(); it != end; ++it)
    {
      if (it != list_.begin())
      {
        output << " ";
      }
      output << it->first;
    }
    return output;
  }

  std::ostream& outputNumbers(std::ostream& output, const list& list_)
  {
    list::const_iterator end = list_.end();
    list::const_iterator begin = list_.begin();
    for (size_t i = 0; i < searchMax(list_); ++i)
    {
      begin = list_.cbegin();
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
      }
      output << "\n";
    }
    return output;
  }
  void calcucationSum(list& list_, numberList& sum)
  {
    list::const_iterator end = list_.end();
    list::const_iterator begin = list_.begin();
    const int max = std::numeric_limits< int >::max();
    for (size_t i = 0; i < searchMax(list_); ++i)
    {
      int summa = 0;
      begin = list_.begin();
      for (; begin != end; ++begin)
      {
        numberList::const_iterator nbegin = begin->second.begin();
        if (i >= begin->second.size())
        {
          continue;
        }
        std::advance(nbegin, i);
        if (max - *nbegin < summa)
        {
          throw std::overflow_error("Overflow for int");
        }
        summa += *nbegin;
      }
      sum.push_back(summa);
    }
  }

  std::ostream& outputSum(std::ostream& output, const numberList& list)
  {
    std::list< int >::const_iterator begin = list.begin();
    for (; begin != list.cend(); ++begin)
    {
      if (begin != list.cbegin())
      {
        output << " ";
      }
      output << *begin;
    }
    return output;
  }
}

std::istream& kiselev::createList(std::istream& input, list& list_)
{
  std::string name;
  while (input >> name)
  {
    numberList numbers;
    int number = 0;
    while (input >> number)
    {
      if (!input)
      {
        throw std::logic_error("Incorrect number");
      }
      numbers.push_back(number);
    }
    input.clear();
    list_.push_back(pair(name, numbers));
  }
  return input;
}

std::ostream& kiselev::output(std::ostream& output, list& list_)
{
  numberList summ;
  calcucationSum(list_, summ);
  outputName(output, list_) << "\n";
  outputNumbers(output, list_);
  outputSum(output, summ) << "\n";
  return output;
}


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

  std::ostream& outputElement(std::ostream& output, const list::const_iterator& list, bool& first)
  {
    if (!first)
    {
      output << " ";
    }
    else
    {
      first = false;
    }
    return output << list->first;
  }

  std::ostream& outputElement(std::ostream& output, const numberList::const_iterator& nums, bool& first)
  {
    if (!first)
    {
      output << " ";
    }
    else
    {
      first = false;
    }
    return output << *nums;
  }

  std::ostream& outputName(std::ostream& output, const list& list_)
  {
    list::const_iterator end = list_.cend();
    bool first = true;
    for (list::const_iterator it = list_.begin(); it != end; ++it)
    {
      outputElement(output, it, first);
    }
    return output;
  }

  std::ostream& outputNumbers(std::ostream& output, const list& list_)
  {
    list::const_iterator end = list_.end();
    list::const_iterator begin = list_.begin();
    for (size_t i = 0; i < searchMax(list_); ++i)
    {
      begin = list_.begin();
      bool first = true;
      for (; begin != end; ++begin)
      {
        numberList::const_iterator nbegin = begin->second.begin();
        if (i >= begin->second.size())
        {
          continue;
        }
        std::advance(nbegin, i); //Сделать у итератора метод +=
        outputElement(output, nbegin, first);
      }
      output << "\n";
    }
    return output;
  }
  void calcucationSum(list& list_, numberList& sum)
  {
    list::const_iterator end = list_.end();
    list::const_iterator begin = list_.begin();
    const unsigned long long max = std::numeric_limits< unsigned long long >::max();
    for (size_t i = 0; i < searchMax(list_); ++i)
    {
      unsigned long long summa = 0;
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
          throw std::overflow_error("Overflow for unsigned long long");
        }
        summa += *nbegin;
      }
      sum.push_back(summa);
    }
  }

  std::ostream& outputSum(std::ostream& output, const numberList& list)
  {
    bool first = true;
    numberList::const_iterator begin = list.begin();
    for (; begin != list.cend(); ++begin)
    {
      outputElement(output, begin, first);
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
    unsigned long long number = 0;
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
  if (list_.empty())
  {
    return output << "0\n";
  }
  numberList summ;
  calcucationSum(list_, summ);
  outputName(output, list_) << "\n";
  if (list_.front().second.empty())
  {
    return output << "0\n";
  }
  outputNumbers(output, list_);
  outputSum(output, summ) << "\n";
  return output;
}


#include "workFlows.hpp"
#include <cstddef>
#include <iterator>
#include <limits>
#include <ostream>
#include <stdexcept>
#include "constIterator.hpp"

namespace
{
  size_t searchMax(const list& list_)
  {
    size_t max = 0;
    for (auto begin = list_.cbegin(); begin != list_.cend(); ++begin)
    {
      max = std::max(max, begin->second.size());
    }
    return max;
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
        std::next(nbegin, i);
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
    for (auto it = list.cbegin(); it != list.cend(); ++it)
    {
      if (it != list.cbegin())
      {
        output << " ";
      }
      output << *it;
    }
    return output;
  }

  std::ostream& outputName(std::ostream& output, const list& list_)
  {
    for (auto it = list_.cbegin(); it != list_.cend(); ++it)
    {
      if (it != list_.cbegin())
      {
        output << " ";
      }
      output << it->first;
    }
    return output;
  }

  std::ostream& outputNumbers(std::ostream& output, const list& list_)
  {
    auto it = list_.cbegin();
    for (size_t i = 0; i < searchMax(list_); ++i)
    {
      it = list_.cbegin();
      for (; it != list_.end(); ++it)
      {
        auto nit = it->second.cbegin();
        if (i >= it->second.size())
        {
          continue;
        }
        std::advance(nit, i);
        if (it != list_.cbegin())
        {
          output << " ";
        }
        output << *nit;
      }
      output << "\n";
      it = list_.cbegin();
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
  outputName(output, list_) << "\n";
  if (list_.front().second.empty())
  {
    return output << "0\n";
  }
  outputNumbers(output, list_);
  numberList summ;
  calcucationSum(list_, summ);
  outputSum(output, summ) << "\n";
  return output;
}


#include "inputProcess.hpp"
#include <iostream>
#include <list>
#include <sstream>
#include <cctype>
#include <limits>

void alymova::inputProcess(std::istream& in, list_pair_t& list)
{
  std::string name;
  while ((in >> name) && (!in.eof()))
  {
    list_int_t list_int;
    int num = 0;
    while ((in >> num))
    {
      list_int.push_back(num);
    }
    pair_t p(name, list_int);
    list.push_back(p);
    if (in.eof())
    {
      break;
      std::cout << "eof\n";
    }
    in.clear();
  }
}
void alymova::outputProcess(std::ostream& out, const list_pair_t& list)
{
  if (list.empty())
  {
    out << "0\n";
    return;
  }

  for (list_pair_citer_t it = list.cbegin(); it != list.cend(); it++)
  {
    if (it != list.cbegin())
    {
      out << " ";
    }
    out << (*it).first;
  }
  out << "\n";

  list_int_t sums;
  size_t max_size = findMaxListSize(list);
  for (size_t i = 0; i < max_size; i++)
  {
    int sum_now = 0;
    bool printed = false;
    for (list_pair_citer_t it = list.cbegin(); it != list.cend(); it++)
    {
      const list_int_t list_now = (*it).second;
      if (list_now.size() > i)
      {
        list_int_citer_t list_now_it = list_now.cbegin();
        for (size_t j = 0; j < i; j++)
        {
          list_now_it++;
        }
        if (printed)
        {
          out << " ";
        }
        out << *list_now_it;
        printed = true;
        if (isOverflowSumInt(sum_now, *list_now_it))
        {
          throw std::logic_error("Summation is impossible");
        }
        sum_now += (*list_now_it);
      }
    }
    sums.push_back(sum_now);
    out << "\n";
  }
  if (sums.empty())
  {
    out << "0\n";
  }
  for (list_int_iter_t it = sums.begin(); it != sums.end(); it++)
  {
    if (it != sums.begin())
    {
      out << " ";
    }
    out << (*it);
  }
}
size_t alymova::findMaxListSize(const list_pair_t& list)
{
  size_t max_size = 0;
  for (list_pair_citer_t it = list.cbegin(); it != list.cend(); it++)
  {
    size_t size_now = (*it).second.size();
    if (size_now > max_size)
    {
      max_size = size_now;
    }
  }
  return max_size;
}
bool alymova::isOverflowSumInt(int a, int b)
{
  return (((a >= 0) && (b > std::numeric_limits< int >::max() - a))
    || ((a < 0) && (b < std::numeric_limits< int >::min() - a)));
}

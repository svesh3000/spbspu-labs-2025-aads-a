#include "LineProcessing.hpp"
#include <stdexcept>

template < class K, class T >
void zakirov::print_d(std::ostream & out, std::string name, const std::map< K, T > & dictionary)
{
  if (dictionary.empty())
  {
    throw std::invalid_argument("<EMPTY>")
  }

  auto iter = dictionary.cbegin();
  out << name;
  for (; iter != dictionary.end(); ++iter)
  {
    out << ' ' << iter->first << ' ' << iter->second;
  }
}

template < class K, class T >
void zakirov::complement_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d)
{

}

template < class K, class T >
void zakirov::intersect_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d)
{
  result_d.clear();
  if (first_d.empty() || second_d.empty())
  {
    return;
  }

  auto first_iter = first_d.cbegin();
  auto second_iter = second_d.cbegin();

  while (first_iter != first_d.cend() && second_iter != second_d.cend())
  {
    if (first_iter->first < second_iter->first)
    {
      ++first_iter;
    }
    else if (first_iter->first > second_iter->first)
    {
      ++second_iter;
    }
    else
    {
      result_d.emplace(first_iter->first, first_iter->second);
      ++second_iter;
      ++first_iter;
    }
  }
}

template < class K, class T >
void zakirov::union_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d)
{

}

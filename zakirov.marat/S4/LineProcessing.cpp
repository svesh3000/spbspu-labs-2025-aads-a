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
void zakirov::complement_d(std::map< K, T > & result_d, std::map< K, T > & first_d, std::map< K, T > & second_d)
{

}

template < class K, class T >
void zakirov::intersect_d(std::map< K, T > & result_d, std::map< K, T > & first_d, std::map< K, T > & second_d)
{

}

template < class K, class T >
void zakirov::union_d(std::map< K, T > & result_d, std::map< K, T > & first_d, std::map< K, T > & second_d)
{

}

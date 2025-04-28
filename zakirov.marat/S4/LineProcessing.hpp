#ifndef LINEPROCESSING_HPP
#define LINEPROCESSING_HPP
#include <iostream>
#include <map>
#include <string>

namespace zakirov
{
  template < class K, class T >
  void print_d(std::ostream & out, std::string name, const std::map< K, T > & dictionary);
  template < class K, class T >
  void complement_d(std::map< K, T > & result_d, std::map< K, T > & first_d, std::map< K, T > & second_d);
  template < class K, class T >
  void intersect_d(std::map< K, T > & result_d, std::map< K, T > & first_d, std::map< K, T > & second_d);
  template < class K, class T >
  void union_d(std::map< K, T > & result_d, std::map< K, T > & first_d, std::map< K, T > & second_d);
}

#endif


#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "nodelist.hpp"

template< typename T >
struct ListIterator
{
  NodeList< T >* node;
  using this_t = ListIterator< T >;

  ListIterator();
  ~ListIterator() = default;
  ListIterator(const this_t&) = default;
  this_t& operator=(const this_t&) = default;
};
#endif
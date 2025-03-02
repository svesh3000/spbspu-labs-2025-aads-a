#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>
#include "NodeFwdList.hpp"

template< class T >
struct IteratorFwd: public std::iterator< std::forward_iterator_tag, int >
{
  NodeFwdList< T >* node;
  using this_t = IteratorFwd< T >;

  IteratorFwd(): node(nullptr) {};
  ~IteratorFwd() = default;
  IteratorFwd(const this_t&) = default;
  this_t& operator=(const this_t&) = default;

  this_t& operator++();
  this_t operator++(int);
  T& operator*();
  T* operator->();
  bool operator!=(const this_t&) const;
  bool operator==(const this_t&) const;
};

#endif
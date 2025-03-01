#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include <iterator>
#include "FwdList.hpp"

template< typename T >
struct IteratorFwd: public std::iterator< std::forward_iterator_tag, int >
{
  NodeFwdList< T >* node_;
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
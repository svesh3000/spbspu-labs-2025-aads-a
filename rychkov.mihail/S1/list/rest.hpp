#ifndef REST_HPP
#define REST_HPP

#include "decl.hpp"

#include <utility>

template< class T >
void rychkov::List< T >::swap(List& rhs) noexcept
{
  std::swap(head_, rhs.head_);
  std::swap(tail_, rhs.tail_);
  std::swap(size_, rhs.size_);
}

#endif


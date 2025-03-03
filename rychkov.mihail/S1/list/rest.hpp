#ifndef REST_HPP
#define REST_HPP

#include "decl.hpp"

#include <utility>
#include <functional>

template< class T >
void rychkov::List< T >::swap(List& rhs) noexcept
{
  std::swap(head_, rhs.head_);
  std::swap(tail_, rhs.tail_);
  std::swap(size_, rhs.size_);
}
template< class T >
void rychkov::List< T >::reverse() noexcept
{
  const_iterator i = begin();
  while (i != end())
  {
    const_iterator temp = i;
    ++i;
    std::swap(temp.node_->prev, temp.node_->next);
  }
  std::swap(head_, tail_);
}

#endif


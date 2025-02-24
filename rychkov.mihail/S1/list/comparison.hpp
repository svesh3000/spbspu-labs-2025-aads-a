#ifndef COMPARISON_HPP
#define COMPARISON_HPP

#include "decl.hpp"

template< class T >
bool rychkov::List< T >::operator==(const List& rhs) const
{
  if (size_ != rhs.size_)
  {
    return false;
  }
  for (const_iterator i = begin(), j = rhs.begin(); (i != end()) && (j != rhs.end()); ++i, ++j)
  {
    if (*i != *j)
    {
      return false;
    }
  }
  return true;
}
template< class T >
bool rychkov::List< T >::operator!=(const List& rhs) const
{
  return !(*this == rhs);
}

#endif

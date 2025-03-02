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
  return compare(rhs, std::equal_to<>());
}
template< class T >
bool rychkov::List< T >::operator!=(const List& rhs) const
{
  return !(*this == rhs);
}
template< class T >
bool rychkov::List< T >::operator<=(const List& rhs) const
{
  return compare(rhs, std::less_equal<>());
}
template< class T >
bool rychkov::List< T >::operator>=(const List& rhs) const
{
  return compare(rhs, std::greater_equal<>());
}
template< class T >
bool rychkov::List< T >::operator<(const List& rhs) const
{
  return compare(rhs, std::less<>());
}
template< class T >
bool rychkov::List< T >::operator>(const List& rhs) const
{
  return compare(rhs, std::greater<>());
}

template< class T >
template< class C >
bool rychkov::List< T >::compare(const List& rhs, C comp) const
{
  const_iterator i = begin(), j = rhs.begin();
  for (; (i != end()) && (j != rhs.end()); ++i, ++j)
  {
    if (!comp(*i, *j))
    {
      return false;
    }
  }
  return true;
}

#endif

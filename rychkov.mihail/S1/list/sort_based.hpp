#ifndef SORT_BASED_HPP
#define SORT_BASED_HPP

#include "decl.hpp"

#include <functional>
#include <utility>

template< class T >
typename rychkov::List< T >::size_type rychkov::List< T >::unique()
{
  return unique(std::equal_to<>());
}
template< class T >
template< class P >
typename rychkov::List< T >::size_type  rychkov::List< T >::unique(P predicate)
{
  size_type result = 0;
  const_iterator i = ++begin(), prev = begin();
  for (; i != end(); prev = i, ++i)
  {
    if (predicate(*i, *prev))
    {
      erase(i);
      result++;
    }
  }
  return result;
}
template< class T >
void rychkov::List< T >::sort()
{
  sort(std::less<>());
}
template< class T >
template< class C >
void rychkov::List< T >::sort(C compare)
{
  if (size_ <= 1)
  {
    return;
  }
  merge_sort(compare, begin(), size_);
}
template< class T >
template< class C >
typename rychkov::List< T >::const_iterator rychkov::List< T >::merge_sort(C& compare, const_iterator from, size_t count)
{
  if (count == 1)
  {
    return ++from;
  }
  const_iterator mid = merge_sort(compare, from, count / 2);
  const_iterator to = merge_sort(compare, mid, (count + 1) / 2);
  unsafeMerge(compare, from, mid, mid, to);
  return to;
}
template< class T >
template< class C >
void rychkov::List< T >::unsafeMerge(C& compare, const_iterator& leftFrom,
    const_iterator& leftTo, const_iterator rightFrom, const_iterator rightTo)
{}
template< class T >
void rychkov::List< T >::merge(List& rhs)
{
  merge(rhs, std::less<>());
}
template< class T >
void rychkov::List< T >::merge(List&& rhs)
{
  merge(rhs);
}
template< class T >
template< class C >
void rychkov::List< T >::merge(List& rhs, C compare)
{
  const_iterator i = begin(), j = rhs.begin();
  for (; j != rhs.end(); ++j)
  {
    for (; (i != end()) && compare(*i, *j); ++i)
    {}
    splice(i, rhs, j, ++const_iterator{j});
  }
}
template< class T >
template< class C >
void rychkov::List< T >::merge(List&& rhs, C compare)
{
  merge(rhs, std::move(compare));
}

#endif

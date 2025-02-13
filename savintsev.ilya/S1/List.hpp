#ifndef LIST_HPP
#define LIST_HPP
#include <iterator>

template< typename T >
class List
{
  T data;
  List< T > * next;
  List< T > * prev;
};

template< typename T>
class ListIterator:
  public std::iterator<std::bidirectional_iterator_tag, int>
{
  List< T > * node;
};

#endif

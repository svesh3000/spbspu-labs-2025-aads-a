#ifndef NODELIST_HPP
#define NODELIST_HPP

template< typename T >
struct NodeList
{
  T data;
  NodeList< T >* next;
};
#endif

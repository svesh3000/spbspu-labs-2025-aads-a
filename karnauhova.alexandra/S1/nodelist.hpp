#ifndef NODELIST_HPP
#define NODELIST_HPP

template< typename T >
class NodeList
{
  T data;
  NodeList< T >* next;
};
#endif

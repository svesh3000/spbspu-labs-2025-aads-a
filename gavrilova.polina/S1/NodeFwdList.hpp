#ifndef NODE_HPP
#define NODE_HPP

template< class T >
struct NodeFwdList
{
  T data;
  NodeFwdList< T >* next;
};

#endif
#ifndef NODE_HPP
#define NODE_HPP

namespace smirnov
{
  template< typename T >
  struct Node
  {
    Node< T > * next;
    T data;
    Node():
      next(nullptr),
      data(T())
    {}
    Node(const T & value):
      next(nullptr),
      data(value)
    {}
  };
}
#endif

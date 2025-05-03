#ifndef NODE_HPP
#define NODE_HPP
namespace brevnov
{
  template< typename T>
  struct Node
  {
    T data;
    Node< T > * next;
    Node< T > * prev;
    Node():
      data(T()),
      next(nullptr),
      prev(nullptr)
    {}
    Node(const T& d):
      data(d),
      next(nullptr),
      prev(nullptr)
    {}
  };
}
#endif

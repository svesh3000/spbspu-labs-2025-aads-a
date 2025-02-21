#ifndef NODE_HPP
#define NODE_HPP

namespace kiselev
{
  template < typename T >
  struct Node
  {
    T data_;
    Node< T >* next_;
    Node< T >* prev_;

    Node(const T& data):
      data_(data),
      next_(nullptr),
      prev_(nullptr)
    {}

    Node(const T& data, Node< T >* next, Node< T >* prev):
      data_(data),
      next_(next),
      prev_(prev)
    {}

    Node():
      data_(T()),
      next_(nullptr),
      prev_(nullptr)
    {}

  };
}
#endif

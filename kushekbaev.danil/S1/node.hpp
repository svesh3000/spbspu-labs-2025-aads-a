#ifndef NODE_HPP
#define NODE_HPP

namespace kushekbaev
{
  template< typename T >
  struct Node
  {
    T data_;
    Node< T >* next_;

    Node(const T& data):
      data_(data),
      next_(nullptr)
    {}

    Node():
      data_(T()),
      next_(nullptr)
    {}

  };
}

#endif

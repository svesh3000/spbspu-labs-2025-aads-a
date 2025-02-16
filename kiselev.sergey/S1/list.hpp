#ifndef LIST_HPP
#define LIST_HPP

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
      prev_(nullptr),
      next_(nullptr)
    {}

    Node():
      data_(T()),
      prev_(nullptr),
      next_(nullptr)
    {}
  };
}
#endif

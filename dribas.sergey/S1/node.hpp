#ifndef NODE_HPP
#define NODE_HPP

#include <utility>

namespace
{
 template < class T >
 class Node
 {
public:
  T data_;
  Node< T >* next_;
  Node< T >* prev_;

  Node():
   data_(T()),
   prev_(nullptr),
   next_(nullptr)
   {}

  Node(T&& data):
    prev_(nullptr),
    next_(nullptr)
  {
    std::move(data);
  }

  Node(const T& data):
    data_(data),
    prev_(nullptr),
    next_(nullptr)
  {}
 };
}

#endif

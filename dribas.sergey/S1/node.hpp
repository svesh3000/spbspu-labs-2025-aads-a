#ifndef NODE_HPP
#define NODE_HPP

namespace
{
 template < class T >
 class Node
 {
public:
  T data_;
  Node< T >* next_;
  Node< T >* prev_;

  Node()
  {
   data_(T()),
   prev_(nullptr),
   next_(nullptr)
   {}
  }

  Node(const& T)
  {
   data_(data),
   prev_(nullptr),
   next_(nullptr)
   {}
  }
 };
}

#endif

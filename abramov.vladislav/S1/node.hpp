#ifndef NODE_HPP
#define NODE_HPP

namespace abramov
{
  template< class T >
  struct Node
  {
    T data_;
    Node *prev_;
    Node *next_;
  };
}
#endif

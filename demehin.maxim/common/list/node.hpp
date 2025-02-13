#ifndef NODE_HPP
#define NODE_HPP

namespace demehin
{
  template< typepename T >
  struct Node
  {
    T data_;
    Node<T>* prev_;
    Node<T>* next_;

    Node(const T& data):
      data(data),
      prev_(nullptr),
      next_(nullptr)
    {}
  };
}

#endif

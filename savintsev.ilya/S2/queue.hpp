#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "dynamic-array.hpp"

namespace savintsev
{
  template< typename T >
  class Queue
  {
  public:
    void push(T rhs);
    void pop();
    T get();
  };
}

#endif

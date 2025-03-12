#ifndef QUEUE_HPP
#define QUEUE_HPP

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

#ifndef STACK_HPP
#define STACK_HPP

namespace savintsev
{
  template< typename T >
  class Stack
  {
  public:
    void push(T rhs);
    void pop();
    T get();
  };
}

#endif

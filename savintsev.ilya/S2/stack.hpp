#ifndef STACK_HPP
#define STACK_HPP
#include "dynamic-array.hpp"

namespace savintsev
{
  template< typename T >
  class Stack
  {
  public:
    void push(T rhs);
    void pop();
    T top();
    const T top() const;
  private:
    Array< T > stack_;
  };

  template <typename T>
  void Stack< T >::push(T rhs)
  {
    stack_.push_back(rhs);
  }

  template <typename T>
  void Stack< T >::pop()
  {
    stack_.pop_back();
  }

  template <typename T>
  const T Stack< T >::top() const
  {
    return stack_.back();
  }

  template <typename T>
  T Stack< T >::top()
  {
    return stack_.back();
  }
}

#endif

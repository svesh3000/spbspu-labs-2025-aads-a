#ifndef STACK_HPP
#define STACK_HPP
#include <list>

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
    std::list< T > stack_;
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
    if (!stack_.empty())
      return stack_.back();
  }

  template <typename T>
  T Stack< T >::top()
  {
    if (!stack_.empty())
      return stack_.back();
  }
}

#endif

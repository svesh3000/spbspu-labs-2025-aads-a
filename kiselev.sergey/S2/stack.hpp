#ifndef STACK_HPP
#define STACK_HPP
#include "dynamicArr.hpp"
namespace kiselev
{
  template< typename T >
  class Stack
  {
  public:

    Stack() = default;
    Stack(const Stack< T >&);
    Stack(Stack< T >&&);
    ~Stack() = default;

    Stack< T >& operator=(const Stack< T >&);
    Stack< T >& operator=(Stack< T >&&);

    T& back();
    void pop();
    void push(T);

    size_t size();
    bool empty();

  private:

    DynamicArr< T > arr_;

  };

  template< typename T >
  Stack< T >::Stack(const Stack< T >& stack):
    arr_(stack.arr_)
  {}

  template< typename T >
  Stack< T >::Stack(Stack< T >&& stack):
    arr_(std::move(stack.arr_))
  {}

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& stack)
  {
    arr_ = stack.arr_;
    return *this;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& stack)
  {
    arr_ = std::move(stack.arr_);
    return *this;
  }

  template< typename T >
  T& Stack< T >::back()
  {
    return arr_.back();
  }

  template< typename T >
  void Stack< T >::pop()
  {
    return arr_.popBack();
  }

  template< typename T >
  void Stack< T >::push(T data)
  {
    arr_.push(data);
  }

  template< typename T >
  size_t Stack< T >::size()
  {
    return arr_.size();
  }

  template< typename T >
  bool Stack< T >::empty()
  {
    return arr_.empty();
  }

}
#endif

#ifndef STACK_HPP
#define STACK_HPP
#include <cstddef>
#include "array.hpp"

namespace alymova
{
  template< typename T >
  struct Stack
  {
    Stack();
    Stack(const Stack< T >& other);
    Stack(Stack< T >&& other);
    ~Stack() = default;

    bool empty() const;
    size_t size() const;
    T& top();
    const T& top() const;
    void push(const T& value);
    void push(T&& value);
    //template< typename... Args >
    //void emplace(Args&&... args);
    void pop();

  private:
    Array< T > data_;
  };

  template< typename T >
  Stack< T >::Stack():
    data_()
  {}

  template< typename T >
  Stack< T >::Stack(const Stack< T >& other):
    data_(other)
  {}

  template< typename T >
  Stack< T >::Stack(Stack< T >&& other):
    data_(std::forward< T >(other.data_))
  {}

  /*template< typename T >
  Stack< T >::~Stack()
  {
    data_.~Array();
  }*/

  template< typename T >
  bool Stack< T >::empty() const
  {
    return (data_.size() == 0);
  }

  template< typename T >
  size_t Stack< T >::size() const
  {
    return data_.size();
  }

  template< typename T >
  T& Stack< T >::top()
  {
    return data_.back();
  }

  template< typename T >
  const T& Stack< T >::top() const
  {
    return data_.back();
  }

  template< typename T >
  void Stack< T >::push(const T& value)
  {
    data_.push_back(value);
  }

  template< typename T >
  void Stack< T >::push(T&& value)
  {
    data_.push_back(std::forward< T >(value));
  }

  template< typename T >
  void Stack< T >::pop()
  {
    data_.pop_back();
  }
}
#endif

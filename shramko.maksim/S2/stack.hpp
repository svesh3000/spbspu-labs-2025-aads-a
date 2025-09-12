#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include "../common/FwdList.hpp"

namespace shramko
{
  template< typename T >
  class Stack
  {
  public:
    Stack() noexcept;
    ~Stack() = default;
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void push(const T& data);
    void push(T&& data);
    void pop();
    size_t size() const noexcept;
    bool empty() const noexcept;
    T& top();
    const T& top() const;
    void swap(Stack& other) noexcept;

  private:
    ForwardList< T > container_;
  };


  template< typename T >
  Stack< T >::Stack() noexcept: container_() {}

  template< typename T >
  Stack< T >::Stack(const Stack& other): container_(other.container_) {}

  template< typename T >
  Stack< T >::Stack(Stack&& other) noexcept: container_(std::move(other.container_)) {}

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack& other)
  {
    if (this != &other)
    {
      container_ = other.container_;
    }
    return *this;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack&& other) noexcept
  {
    if (this != &other)
    {
      container_ = std::move(other.container_);
    }
    return *this;
  }

  template< typename T >
  void Stack< T >::push(const T& data)
  {
    container_.addToFront(data);
  }

  template< typename T >
  void Stack< T >::push(T&& data)
  {
    container_.addToFront(std::move(data));
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (container_.isEmpty())
    {
      throw std::logic_error("Stack is empty");
    }
    container_.removeFront();
  }

  template< typename T >
  size_t Stack< T >::size() const noexcept
  {
    return container_.getSize();
  }

  template< typename T >
  bool Stack< T >::empty() const noexcept
  {
    return container_.isEmpty();
  }

  template< typename T >
  T& Stack< T >::top()
  {
    if (container_.isEmpty())
    {
      throw std::logic_error("Stack is empty");
    }
    return container_.getFront();
  }

  template< typename T >
  const T& Stack< T >::top() const
  {
    if (container_.isEmpty())
    {
      throw std::logic_error("Stack is empty");
    }
    return container_.getFront();
  }

  template< typename T >
  void Stack< T >::swap(Stack& other) noexcept
  {
    container_.swapLists(other.container_);
  }
}

#endif

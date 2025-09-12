#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <utility>
#include <stdexcept>
#include "../common/FwdList.hpp"

namespace shramko
{
  template< typename T >
  class Queue
  {
  public:
    Queue() noexcept;
    ~Queue() = default;
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;

    void push(const T& data);
    void push(T&& data);
    void pop();
    size_t size() const noexcept;
    bool empty() const noexcept;
    T& front();
    const T& front() const;
    void swap(Queue& other) noexcept;

  private:
    ForwardList< T > container_;
  };


  template< typename T >
  Queue< T >::Queue() noexcept: container_() {}

  template< typename T >
  Queue< T >::Queue(const Queue& other): container_(other.container_) {}

  template< typename T >
  Queue< T >::Queue(Queue&& other) noexcept: container_(std::move(other.container_)) {}

  template< typename T >
  Queue< T >& Queue< T >::operator=(const Queue& other)
  {
    if (this != &other)
    {
      container_ = other.container_;
    }
    return *this;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(Queue&& other) noexcept
  {
    if (this != &other)
    {
      container_ = std::move(other.container_);
    }
    return *this;
  }

  template< typename T >
  void Queue< T >::push(const T& data)
  {
    container_.addToBack(data);
  }

  template< typename T >
  void Queue< T >::push(T&& data)
  {
    container_.addToBack(std::move(data));
  }

  template< typename T >
  void Queue< T >::pop()
  {
    if (container_.isEmpty())
    {
      throw std::logic_error("Queue is empty");
    }
    container_.removeFront();
  }

  template< typename T >
  size_t Queue< T >::size() const noexcept
  {
    return container_.getSize();
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return container_.isEmpty();
  }

  template< typename T >
  T& Queue< T >::front()
  {
    if (container_.isEmpty())
    {
      throw std::logic_error("Queue is empty");
    }
    return container_.getFront();
  }

  template< typename T >
  const T& Queue< T >::front() const
  {
    if (container_.isEmpty())
    {
      throw std::logic_error("Queue is empty");
    }
    return container_.getFront();
  }

  template< typename T >
  void Queue< T >::swap(Queue& other) noexcept
  {
    container_.swapLists(other.container_);
  }
}

#endif

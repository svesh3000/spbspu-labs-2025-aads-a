#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include <exception>
#include "dynamicArr.hpp"
namespace kiselev
{
  template< typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >&);
    Queue(Queue< T >&&) noexcept;
    ~Queue() = default;

    Queue< T >& operator=(const Queue< T >&);
    Queue< T >& operator=(Queue< T >&&) noexcept;

    T& front() noexcept;
    const T& front() const noexcept;
    T& back() noexcept;
    const T& back() const noexcept;

    void pop() noexcept;
    void push(T&) noexcept;
    void push(T&&) noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:

    DynamicArr< T > arr_;

  };

  template< typename T >
  Queue< T >::Queue(const Queue< T >& queue):
    arr_(queue.arr_)
  {}

  template< typename T >
  Queue< T >::Queue(Queue< T >&& queue) noexcept:
    arr_(std::move(queue.arr_))
  {}

  template< typename T >
  Queue< T >& Queue< T >::operator=(const Queue< T >& queue)
  {
    arr_ = queue.arr_;
    return *this;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& queue) noexcept
  {
    arr_ = std::move(queue.arr_);
    return *this;
  }

  template< typename T >
  T& Queue< T >::front() noexcept
  {
    return arr_.front();
  }

  template< typename T >
  const T& Queue< T >::front() const noexcept
  {
    return arr_.front();
  }

  template< typename T >
  T& Queue< T >::back() noexcept
  {
    return arr_.back();
  }

  template< typename T >
  const T& Queue< T >::back() const noexcept
  {
    return arr_.back();
  }

  template< typename T >
  void Queue< T >::pop() noexcept
  {
    arr_.popFront();
  }

  template< typename T >
  void Queue< T >::push(T& data) noexcept
  {
    arr_.push(data);
  }

  template< typename T >
  void Queue< T >::push(T&& data) noexcept
  {
    arr_.push(data);
  }

  template< typename T >
  size_t Queue< T >::size() const noexcept
  {
    return arr_.size();
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return arr_.empty();
  }
}

#endif

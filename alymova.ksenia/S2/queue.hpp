#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include "array.hpp"

namespace alymova
{
  template< typename T >
  struct Queue
  {
    Queue();
    Queue(const Queue< T >& other);
    Queue(Queue< T >&& other);
    ~Queue() = default;

    bool empty() const;
    size_t size() const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push(const T& value);
    void push(T&& value);
    //template< typename... Args >
    //void emplace(Args&&... args);
    void pop();

  private:
    Array< T > data_;
  };

  template< typename T >
  Queue< T >::Queue():
    data_()
  {}

  template< typename T >
  Queue< T >::Queue(const Queue< T >& other):
    data_(other)
  {}

  template< typename T >
  Queue< T >::Queue(Queue< T >&& other):
    data_(std::forward< T >(other.data_))
  {}

  /*template< typename T >
  Queue< T >::~Queue()
  {
    data_.~Array();
  }*/

  template< typename T >
  bool Queue< T >::empty() const
  {
    return data_.size() == 0;
  }

  template< typename T >
  size_t Queue< T >::size() const
  {
    return data_.size();
  }

  template< typename T >
  T& Queue< T >::front()
  {
    return data_.front();
  }

  template< typename T >
  const T& Queue< T >::front() const
  {
    return data_.front();
  }

  template< typename T >
  T& Queue< T >::back()
  {
    return data_.back();
  }

  template< typename T >
  const T& Queue< T >::back() const
  {
    return data_.back();
  }

  template< typename T >
  void Queue< T >::push(const T& value)
  {
    data_.push_back(value);
  }

  template< typename T >
  void Queue< T >::push(T&& value)
  {
    data_.push_back(std::forward< T >(value));
  }

  template< typename T >
  void Queue< T >::pop()
  {
    data_.pop_front();
  }
}
#endif

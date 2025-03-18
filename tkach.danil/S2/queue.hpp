#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include "dynamic_array.hpp"

namespace tkach
{
  template< typename T >
  class Queue
  {
  public:
    Queue() = default;
    void pop();
    void push(const T& data);
    void push(T&& data);
    size_t size() const noexcept;
    bool empty() const noexcept;
    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
  private:
    DynArray< T > array_;
  };

  template< typename T >
  void Queue< T >::pop()
  {
    array_.popFront();
  }

  template< typename T >
  void Queue< T >::push(const T& data)
  {
    array_.pushBack(data);
  }

  template< typename T >
  void Queue< T >::push(T&& data)
  {
    array_.pushBack(std::move(data));
  }

  template< typename T >
  size_t Queue< T >::size() const noexcept
  {
    return array_.size();
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return array_.empty();
  }

  template< typename T >
  T& Queue< T >::back()
  {
    return const_cast< T& >(static_cast< const Queue< T >* >(this)->back());
  }

  template< typename T >
  const T& Queue< T >::back() const
  {
    return array_.back();
  }

  template< typename T >
  T& Queue< T >::front()
  {
    return const_cast< T& >(static_cast< const Queue< T >* >(this)->front());
  }

  template< typename T >
  const T& Queue< T >::front() const
  {
    return array_.front();
  }
}

#endif
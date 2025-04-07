#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cassert>
#include <cstddef>
#include <stdexcept>

namespace lanovenko
{
  template< typename T >
  class Queue
  {
  public:
    ~Queue() = default;
    Queue() = default;
    Queue(const Queue&) = default;
    Queue(Queue&&) = default;
    Queue& operator=(const Queue&) = default;
    Queue& operator=(Queue&&) = default;
    size_t size() const noexcept;
    bool empty() const noexcept;
    T& front() noexcept;
    T& back() noexcept;
    void push(const T& value);
    void pop() noexcept;
  private:
    size_t size_;
    size_t first_;
    static const size_t max_size_2 = 20;
    T data_[max_size_2];
  };
}

template< typename T >
size_t lanovenko::Queue< T >::size() const noexcept
{
  return size_;
}

template< typename T >
bool lanovenko::Queue< T >::empty() const noexcept
{
  return size_ == 0;
}

template< typename T >
T& lanovenko::Queue< T >::front() noexcept
{
  assert(!this->empty());
  return data_[first_];
}

template < typename T >
T& lanovenko::Queue< T >::back() noexcept
{
  assert(!this->empty());
  return data_[size_ - 1];
}

template< typename T >
void lanovenko::Queue< T >::push(const T& value)
{
  if (size_ == max_size_2)
  {
    throw std::logic_error("Queue overflow");
  }
  data_[size_++] = value;
}

template< typename T >
void lanovenko::Queue< T >::pop() noexcept
{
  assert(!this->empty());
  size_--;
  if (size_ != 0)
  {
    first_++;
  }
}

#endif

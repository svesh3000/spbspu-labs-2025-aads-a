#ifndef STACK_HPP
#define STACK_HPP

#include <cassert>
#include <cstddef>
#include <stdexcept>

namespace lanovenko
{
  template< typename T >
  class Stack
  {
  public:
    ~Stack() = default;
    Stack() = default;
    Stack(const Stack& rhs) = default;
    Stack(Stack&& rhs) = default;
    Stack& operator=(const Stack& rhs) = default;
    Stack& operator=(Stack&& rhs) = default;
    void push(const T& data);
    size_t size() const noexcept;
    void pop() noexcept;
    T& top() noexcept;
    bool empty();
  private:
    size_t size_;
    static const size_t max_size_ = 100;
    T data_[max_size_];
  };
}

template< typename T >
size_t lanovenko::Stack< T >::size() const noexcept
{
  return size_;
}

template< typename T >
T& lanovenko::Stack< T >::top() noexcept
{
  assert(!this->empty());
  return data_[size_ - 1];
}

template< typename T >
bool lanovenko::Stack< T >::empty()
{
  return size_ == 0;
}

template< typename T >
void lanovenko::Stack< T >::pop() noexcept
{
  assert(!this->empty());
  size_--;
}

template< typename T >
void lanovenko::Stack< T >::push(const T& data)
{
  if (size_ == max_size_)
  {
    throw std::logic_error("Stack overflow!");
  }
  data_[size_] = data;
  size_++;
}

#endif

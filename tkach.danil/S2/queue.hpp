#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "dynamic_array.hpp"

namespace tkach
{
  template< typename T >
  class Queue
  {
  public:
    void pop();
    void push(const T& data);
    void push(T&& data);
    void empty() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
  private:
    DynArray< T > array_;
  };
}

#endif
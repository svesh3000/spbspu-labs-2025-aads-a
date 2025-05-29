#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include <list>
#include <stdexcept>
#include <utility>
#include "../S1/fwd_list.hpp"

namespace zakirov
{
  template < class T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue & other);
    Queue(Queue && other) noexcept;
    ~Queue() = default;
    bool empty();
    size_t size();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    void push (const T & value);
    void push (T && value);
    void pop();
  private:
    template < class U >
    void uni_push(U && value);
    void add_capacity();
    T * data_;
    size_t first_;
    size_t size_;
    size_t capacity_;
  };

  template < typename T >
  Queue< T >::Queue():
    data_(nullptr),
    first_(0),
    size_(0),
    capacity_(0)
  {}

  template < typename T >
  Queue< T >::Queue(const Queue & other):
    data_(other.data_),
    first_(other.first_),
    size_(other.size_),
    capacity_(other.capacity_)
  {}

  template < typename T >
  Queue< T >::Queue(Queue && other) noexcept:
    Queue(other)
  {}

  template < typename T >
  bool Queue< T >::empty()
  {
    return size_ == 0;
  }

  template < typename T >
  size_t Queue< T >::size()
  {
    return size_;
  }

  template < typename T >
  T & Queue< T >::front()
  {
    return data_[0];
  }

  template < typename T >
  const T & Queue< T >::front() const
  {
    return data_[0];
  }

  template < typename T >
  T & Queue< T >::back()
  {
    return data_[size_ - 1];
  }

  template < typename T >
  const T & Queue< T >::back() const
  {
    return data_[size_ - 1];
  }

  template < class T >
  template < class U >
  void Queue< T >::uni_push(U && value)
  {
    if (first_ + size_ > capacity_)
    {
      if (first_ != 0)
      {
        for (size_t i = 0, j = first_; j < first_ + size_; ++i, ++j)
        {
          data_[i] = std::move(data_[j]);
        }

        first_ = 0;
      }
      else
      {
        add_capacity();
      }
    }

    data_[first_ + size_] = std::forward< U >(value);
    ++size_;
  }

  template < typename T >
  void Queue< T >::push(const T & value)
  {
    uni_push(value);
  }

  template < typename T >
  void Queue< T >::push(T && value)
  {
    uni_push(std::move(value));
  }

  template < typename T >
  void Queue< T >::pop()
  {
    ++first_;
  }

  template < typename T >
  void Queue< T >::add_capacity()
  {
    size_t new_capacity = capacity_ * 2 + 1;
    T * new_data = new T[new_capacity];
    for (size_t i = 0, j = first_; j < first_ + size_; ++i, ++j)
    {
      new_data[i] = std::move(data_[j]);
    }

    delete[] data_;
    data_ = new_data;
    first_ = 0;
    capacity_ = new_capacity;
  }
}

#endif

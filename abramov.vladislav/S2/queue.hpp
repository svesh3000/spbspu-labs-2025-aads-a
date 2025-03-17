#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include <algorithm>

namespace abramov
{
  template< class T >
  struct Queue
  {
    Queue();
    Queue(const Queue< T > &queue);
    Queue(Queue< T > &&queue);
    ~Queue();
    Queue< T > &operator=(const Queue< T > &queue);
    Queue< T > &operator=(Queue< T > &&queue);
    void push(const T &rhs);
    T &front();
    const T &front() const;
    void pop();
    size_t size() const;
    bool empty() const;
    void swap(Queue< T > &queue) noexcept;
  private:
    T *data_;
    size_t size_;
    size_t capacity_;

    void clear();
  };

  template< class T >
  Queue< T >::Queue():
    data_(nullptr),
    size_(0),
    capacity_(0)
  {}

  template< class T >
  Queue< T >::Queue(const Queue< T > &queue):
    data_(nullptr),
    size_(0),
    capacity_(0)
  {
    T **data = new T*[queue.capacity_];
    size_t count = 0;
    try
    {
      for (size_t i = 0; i < queue.size_; ++i)
      {
        data[i] = new T(queue.data_[i]);
      }
    }
    catch (const std::bad_alloc &)
    {
      for (size_t i = 0; i < count; ++i)
      {
        delete data[i];
      }
    }
    data_ = data;
    size_ = queue.size_;
    capacity_ = queue.capacity_;
  }

  template< class T >
  Queue< T > &Queue< T >::operator=(const Queue< T > &queue)
  {
    Queue< T > copy(queue);
    clear();
    swap(copy);
    return *this;
  }

  template< class T >
  Queue< T >::Queue(Queue< T > &&queue):
    data_(queue.data_),
    size_(queue.size_),
    capacity_(queue.capacity_)
  {
    queue.data_ = nullptr;
  }

  template< class T >
  Queue< T > &Queue< T >::operator=(Queue< T > &&queue)
  {
    Queue< T > copy(queue);
    clear();
    swap(copy);
    return *this;
  }

  template< class T >
  Queue< T >::~Queue()
  {
    clear();
  }

  template< class T >
  void Queue< T >::push(const T &rhs)
  {
    if (capacity_ == size_)
    {
      T *new_data = expandArray(data_, capacity_);
      delete data_;
      data_ = new_data;
    }
    data_[size_] = new T(rhs);
    ++size_;
  }

  template< class T >
  const T &Queue< T >::front() const
  {
    return data_[0];
  }

  template< class T >
  T &Queue< T >::front()
  {
    return const_cast< T& >(const_cast< const Queue< T >* >(this)->front());
  }

  template< class T >
  void Queue< T >::pop()
  {
    delete data_[0];
    for (size_t i = 0; i < --size_; ++i)
    {
      data_[i] = data_[i + 1];
    }
  }

  template< class T >
  size_t Queue< T >::size() const
  {
    return size_;
  }

  template< class T >
  bool Queue< T >::empty() const
  {
    return size_ == 0;
  }

  template< class T >
  void Queue< T >::swap(Queue< T > &queue) noexcept
  {
    std::swap(data_, queue.data_);
    std::swap(size_, queue.size_);
    std::swap(capacity_, queue.capacity_);
  }

  template< class T >
  void Queue< T >::clear()
  {
    for (size_t i = 0; i < size_; ++i)
    {
      delete data_[i];
    }
    delete data_;
    size_ = 0;
    capacity_ = 0;
  }
}
#endif

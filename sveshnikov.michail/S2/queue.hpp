#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <cstddef>
#include <algorithm>

namespace sveshnikov
{
  template < class T >
  class Queue
  {
  public:
    explicit Queue();
    Queue(const Queue &other);
    Queue(Queue &&other);
    ~Queue();
    Queue< T > &operator=(const Queue &other);
    Queue< T > &operator=(Queue &&other) noexcept;

    T &front() noexcept;
    const T &front() const noexcept;
    size_t getSize() noexcept;
    bool empty() noexcept;
    void push(const T &data);
    void push(T &&data);
    void pop();
    void swap(Queue &other);

  private:
    size_t capacity_;
    T *data_;
    size_t size_;
    size_t first_;
    void resize();
  };

  template < class T >
  Queue< T >::Queue():
    capacity_(100),
    data_(new T[capacity_]),
    size_(0)
  {}

  template < class T >
  Queue< T >::Queue(const Queue &other):
    capacity_(other.capacity_),
    data_(new T[other.capacity_]),
    size_(other.size_)
  {
    for (size_t i = 0; i < other.size_; i++)
    {
      data_[i] = other.data_[i];
    }
  }

  template < class T >
  Queue< T >::Queue(Queue &&other):
    capacity_(other.capacity_),
    data_(other.data_),
    size_(other.size_)
  {
    other.data_ = nullptr;
  }

  template < class T >
  Queue< T >::~Queue()
  {
    delete[] data_;
  }

  template < class T >
  Queue< T > &Queue< T >::operator=(const Queue &other)
  {
    if (*this != std::addressof(other))
    {
      Queue rhs(other);
      swap(rhs);
    }
    return *this;
  }

  template < class T >
  Queue< T > &Queue< T >::operator=(Queue &&other) noexcept
  {
    swap(other);
    return *this;
  }

  template < class T >
  T &Queue< T >::front() noexcept
  {
    return const_cast< T & >(static_cast< const Queue< T > & >(*this).top());
    ;
  }

  template < class T >
  const T &Queue< T >::front() const noexcept
  {
    assert(!empty());
    return data[size - 1];
  }

  template < class T >
  size_t Queue< T >::getSize() noexcept
  {
    return size_;
  }

  template < class T >
  bool Queue< T >::empty() noexcept
  {
    return size_ == 0;
  }

  template < class T >
  void Queue< T >::resize()
  {
    if (size_ == capacity_)
    {
      capacity_ += 100;
      T *new_data = new T[capacity_];
      for (size_t i = 0; i < size_; i++)
      {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
    }
  }

  template < class T >
  void Queue< T >::push(const T &data)
  {
    resize();
    data_[size_] = data;
    size_++;
  }

  template < class T >
  void Queue< T >::push(T &&data)
  {
    resize();
    data_[size_] = std::move(data);
    size_++;
  }

  template < class T >
  void Queue< T >::pop()
  {
    assert(!empty());
    delete data_[--size_];
  }

  template < class T >
  void Queue< T >::swap(Queue &other)
  {
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
  }
}

#endif

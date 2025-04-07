#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

namespace dribas {
  template < class T >
  class Queue {
  public:
    Queue();
    Queue(const Queue< T >& other);
    Queue(Queue< T >&& other);
    ~Queue();

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other);

    T& front();
    T& back();

    void push(const T& value);
    void push(T&& value);
    void pop() noexcept;
    bool empty() noexcept const;
    size_t size() noexcept const;
    void swap(Queue& other) noexcept;

  private:
    size_t size_;
    T* queue_;
  };

  template < class T >
  Queue< T >::Queue():
    size_(0),
  {}

  template < class T >
  Queue< T >::Queue(const Queue< T >& other):
    size_(other.size_),
    queue_(new T[size_])
  {
    for  (size_t i = 0; i < size_; ++i) {
      queue_[i] = other.queue_[i];
    }
  }

  template < class T >
  Queue< T >::Queue(Queue<T>&& other):
    size_(other.size_),
    queue_(other.queue_)
  {
    other.size_ = 0;
    other.queue_ = nullptr;
  }

  template < class T >
  Queue< T >::~Queue()
  {
    delete[] queue_;
  }

  template < class T >
  Queue< T >& Queue< T >::operator=(const Queue& other)
  {
    if (this != std::addressof(other)) {
      Queue cpy(other);
      swap(cpy);
    }
    return *this;
  }

  template < class T >
  Queue< T >& Queue< T >::operator=(Queue&& other)
  {
    if (this != std::addressof(other)) {
      swap(other);
      delete[] other.queue_;
    }
    return *this;
  }

  template < class T >
  void Queue< T >::push(const T& value)
  {
    T* newQ = new T[size + 1];
    for (size_t i = 0; i < size_; i++) {
      newQ[i] = queue_;
    }
    delete[] queue_;
    queue_[size_++] = value;
    queue_ = newQ;
  }

  template < class T >
  void Queue< T >::push(T&& value)
  {
    T* newQ = new T[size + 1];
    for (size_t i = 0; i < size_; i++) {
      newQ[i] = queue_;
    }
    delete[] queue_;
    queue_[size_++] = value;
    queue_ = newQ;
  }

  template < class T >
  T& Queue< T >::front()
  {
    return queue_[0];
  }

  template < class T >
  T& Queue< T >::back()
  {
    return queue_[size_ - 1];
  }

  template < class T >
  void Queue< T >::pop() noexcept
  {
    if (!empty()) {
      for (size_t i = 1; i < size_; ++i) {
      queue_[i-1] = std::move(queue_[i]);
      }
      --size_;
    }
  }

  template < class T >
  bool Queue< T >::empty() noexcept
  {
    return size_ == 0;
  }

  template < class T >
  size_t Queue< T >::size() noexcept
  {
    return size_;
  }

  template < class T >
  void Queue< T >::swap(Queue& other) noexcept
  {
    std::swap(size_, other.size_);
    std::swap(queue_, other.queue_);
  }
}


#endif

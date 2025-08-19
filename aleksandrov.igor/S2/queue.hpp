#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <cassert>
#include <limits>
#include <utility>
#include <stdexcept>

namespace aleksandrov
{
  constexpr size_t minQueueCapacity = 64;

  template< class T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue&);
    Queue(Queue&&) noexcept;
    ~Queue() noexcept;

    Queue& operator=(const Queue&);
    Queue& operator=(Queue&&) noexcept;

    T& front();
    const T& front() const;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t maxSize() const noexcept;
    size_t capacity() const noexcept;
    void shrinkToFit();

    void clear() noexcept;
    void push(const T&);
    void push(T&&);
    template< class... Args >
    void emplace(Args&&...);
    void pop() noexcept;
    void swap(Queue&) noexcept;

    bool operator==(const Queue&) const;
    bool operator!=(const Queue&) const;

  private:
    T* data_;
    size_t first_;
    size_t size_;
    size_t capacity_;

    T* copyData(const Queue& other);
    void resize();
    size_t getBiggerCapacity(size_t capacity) const noexcept;
  };

  template< class T >
  Queue< T >::Queue():
    data_(nullptr),
    first_(0),
    size_(0),
    capacity_(0)
  {}

  template< class T >
  Queue< T >::Queue(const Queue& rhs):
    data_(copyData(rhs)),
    first_(rhs.first_),
    size_(rhs.size_),
    capacity_(rhs.capacity_)
  {}

  template< class T >
  Queue< T >::Queue(Queue&& rhs) noexcept:
    data_(std::exchange(rhs.data_, nullptr)),
    first_(std::exchange(rhs.first_, 0)),
    size_(std::exchange(rhs.size_, 0)),
    capacity_(std::exchange(rhs.capacity_, 0))
  {}

  template< class T >
  Queue< T >::~Queue() noexcept
  {
    clear();
    operator delete(data_);
  }

  template< class T >
  Queue< T >& Queue< T >::operator=(const Queue& rhs)
  {
    Queue copy(rhs);
    swap(copy);
    return *this;
  }

  template< class T >
  Queue< T >& Queue< T >::operator=(Queue&& rhs) noexcept
  {
    Queue copy(std::move(rhs));
    swap(copy);
    return *this;
  }

  template< class T >
  T& Queue< T >::front()
  {
    assert(!empty() && "Cannot access to element in empty queue!");
    return const_cast< T& >(static_cast< const Queue& >(*this).front());
  }

  template< class T >
  const T& Queue< T >::front() const
  {
    assert(!empty() && "Cannot access to element in empty queue!");
    return data_[first_];
  }

  template< class T >
  bool Queue< T >::empty() const noexcept
  {
    return !size_;
  }

  template< class T >
  size_t Queue< T >::size() const noexcept
  {
    return size_;
  }

  template< class T >
  size_t Queue< T >::maxSize() const noexcept
  {
    return std::numeric_limits< size_t >::max();
  }

  template< class T >
  size_t Queue< T >::capacity() const noexcept
  {
    return capacity_;
  }

  template< class T >
  void Queue< T >::shrinkToFit()
  {
    if (capacity_ == size_)
    {
      return;
    }
    else if (capacity_ > size_)
    {
      T* newData = static_cast< T* >(operator new(size_ * sizeof(T)));
      size_t i = first_;
      try
      {
        for (; i < size_ + first_; i = (i + 1) % capacity_)
        {
          new (newData + i) T(std::move_if_noexcept(data_[i]));
        }
      }
      catch (...)
      {
        for (size_t j = first_; j < i + first_; j = (j + 1) % i)
        {
          newData[j].~T();
        }
        operator delete(newData);
        throw;
      }
      for (size_t i = first_; i < size_ + first_; i = (i + 1) % capacity_)
      {
        data_[i].~T();
      }
      operator delete(data_);
      data_ = newData;
      capacity_ = size_;
    }
  }

  template< class T >
  void Queue< T >::clear() noexcept
  {
    while (!empty())
    {
      pop();
    }
  }

  template< class T >
  void Queue< T >::push(const T& value)
  {
    emplace(value);
  }

  template< class T >
  void Queue< T >::push(T&& value)
  {
    emplace(std::move(value));
  }

  template< class T >
  template< class... Args >
  void Queue< T >::emplace(Args&&... args)
  {
    if (size_ == capacity_)
    {
      resize();
    }
    size_t shift = (first_ + size_) % capacity_;
    new (data_ + shift) T(std::forward< Args >(args)...);
    ++size_;
  }

  template< class T >
  void Queue< T >::pop() noexcept
  {
    assert(!empty() && "Cannot delete element from empty queue!");
    data_[first_].~T();
    first_ = size_ == 1 ? 0 : (first_ + 1) % capacity_;
    --size_;
  }

  template< class T >
  void Queue< T >::swap(Queue& other) noexcept
  {
    std::swap(data_, other.data_);
    std::swap(first_, other.first_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template< class T >
  bool Queue< T >::operator==(const Queue& rhs) const
  {
    if (size_ != rhs.size_)
    {
      return false;
    }
    for (size_t i = first_; i < first_ + size_; i = (i + 1) % capacity_)
    {
      if (data_[i] != rhs.data_[i])
      {
        return false;
      }
    }
    return true;
  }

  template< class T >
  bool Queue< T >::operator!=(const Queue& rhs) const
  {
    return !operator==(rhs);
  }

  template< class T >
  T* Queue< T >::copyData(const Queue& other)
  {
    if (!other.capacity_)
    {
      return nullptr;
    }
    T* newData = static_cast< T* >(operator new(other.capacity_ * sizeof(T)));
    size_t i = other.first_;
    try
    {
      for (; i < other.size_ + other.first_; i = (i + 1) % other.capacity_)
      {
        new (newData + i) T(other.data_[i]);
      }
    }
    catch (...)
    {
      for (size_t j = other.first_; j < i + other.first_; j = (j + 1) % i)
      {
        newData[j].~T();
      }
      operator delete(newData);
      throw;
    }
    return newData;
  }

  template< class T >
  void Queue< T >::resize()
  {
    if (!capacity_)
    {
      data_ = static_cast< T* >(operator new(minQueueCapacity * sizeof(T)));
      capacity_ = minQueueCapacity;
      return;
    }
    size_t newCapacity = getBiggerCapacity(capacity_);
    if (newCapacity == capacity_)
    {
      throw std::overflow_error("Reached maximum possible queue capacity!");
    }
    T* newData = static_cast< T* >(operator new(newCapacity * sizeof(T)));
    size_t i = 0;
    try
    {
      for (size_t j = first_; i < size_; ++i, j = (j + 1) % capacity_)
      {
        new (newData + i) T(std::move_if_noexcept(data_[j]));
      }
    }
    catch (...)
    {
      for (size_t j = 0; j < i; ++j)
      {
        newData[j].~T();
      }
      operator delete(newData);
      throw;
    }
    i = 0;
    for (size_t j = first_; i < size_; ++i, j = (j + 1) % capacity_)
    {
      data_[j].~T();
    }
    operator delete(data_);
    data_ = newData;
    first_ = 0;
    capacity_ = newCapacity;
  }

  template< class T >
  size_t Queue< T >::getBiggerCapacity(size_t capacity) const noexcept
  {
    if (!capacity)
    {
      return minQueueCapacity;
    }
    if (capacity > maxSize() / 2)
    {
      return capacity;
    }
    return capacity * 2;
  }
}

#endif


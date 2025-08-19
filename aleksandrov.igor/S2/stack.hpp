#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <cassert>
#include <limits>
#include <utility>
#include <stdexcept>

namespace aleksandrov
{
  constexpr size_t minStackCapacity = 64;

  template< class T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack&);
    Stack(Stack&&) noexcept;
    ~Stack() noexcept;

    Stack& operator=(const Stack&);
    Stack& operator=(Stack&&) noexcept;

    T& top();
    const T& top() const;

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
    void swap(Stack&) noexcept;

    bool operator==(const Stack&) const;
    bool operator!=(const Stack&) const;

  private:
    T* data_;
    size_t last_;
    size_t size_;
    size_t capacity_;

    T* copyData(const Stack& other);
    void resize();
    size_t getBiggerCapacity(size_t capacity) const noexcept;
  };

  template< class T >
  Stack< T >::Stack():
    data_(nullptr),
    last_(0),
    size_(0),
    capacity_(0)
  {}

  template< class T >
  Stack< T >::Stack(const Stack& rhs):
    data_(copyData(rhs)),
    last_(rhs.last_),
    size_(rhs.size_),
    capacity_(rhs.capacity_)
  {}

  template< class T >
  Stack< T >::Stack(Stack&& rhs) noexcept:
    data_(std::exchange(rhs.data_, nullptr)),
    last_(std::exchange(rhs.last_, 0)),
    size_(std::exchange(rhs.size_, 0)),
    capacity_(std::exchange(rhs.capacity_, 0))
  {}

  template< class T >
  Stack< T >::~Stack() noexcept
  {
    clear();
    operator delete(data_);
  }

  template< class T >
  Stack< T >& Stack< T >::operator=(const Stack& rhs)
  {
    Stack copy(rhs);
    swap(copy);
    return *this;
  }

  template< class T >
  Stack< T >& Stack< T >::operator=(Stack&& rhs) noexcept
  {
    Stack copy(std::move(rhs));
    swap(copy);
    return *this;
  }

  template< class T >
  T& Stack< T >::top()
  {
    assert(!empty() && "Cannot access to element in empty stack!");
    return const_cast< T& >(static_cast< const Stack& >(*this).top());
  }

  template< class T >
  const T& Stack< T >::top() const
  {
    assert(!empty() && "Cannot access to element in empty stack!");
    return data_[last_];
  }

  template< class T >
  bool Stack< T >::empty() const noexcept
  {
    return !size_;
  }

  template< class T >
  size_t Stack< T >::size() const noexcept
  {
    return size_;
  }

  template< class T >
  size_t Stack< T >::maxSize() const noexcept
  {
    return std::numeric_limits< size_t >::max();
  }

  template< class T >
  size_t Stack< T >::capacity() const noexcept
  {
    return capacity_;
  }

  template< class T >
  void Stack< T >::shrinkToFit()
  {
    if (capacity_ == size_)
    {
      return;
    }
    else if (capacity_ > size_)
    {
      T* newData = static_cast< T* >(operator new(size_ * sizeof(T)));
      size_t i = 0;
      try
      {
        for (; i < size_; ++i)
        {
          new (newData + i) T(std::move_if_noexcept(data_[i]));
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
      for (size_t i = 0; i < size_; ++i)
      {
        data_[i].~T();
      }
      operator delete(data_);
      data_ = newData;
      capacity_ = size_;
    }
  }

  template< class T >
  void Stack< T >::clear() noexcept
  {
    while (!empty())
    {
      pop();
    }
  }

  template< class T >
  void Stack< T >::push(const T& value)
  {
    emplace(value);
  }

  template< class T >
  void Stack< T >::push(T&& value)
  {
    emplace(std::move(value));
  }

  template< class T >
  template< class... Args >
  void Stack< T >::emplace(Args&&... args)
  {
    if (size_ == capacity_)
    {
      resize();
    }
    size_t shift = size_ ? ++last_ : 0;
    new (data_ + shift) T(std::forward< Args >(args)...);
    ++size_;
  }

  template< class T >
  void Stack< T >::pop() noexcept
  {
    assert(!empty() && "Trying to delete from empty stack!");
    data_[last_].~T();
    last_ = size_ == 1 ? 0 : last_ - 1;
    --size_;
  }

  template< class T >
  void Stack< T >::swap(Stack& other) noexcept
  {
    std::swap(data_, other.data_);
    std::swap(last_, other.last_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template< class T >
  bool Stack< T >::operator==(const Stack& other) const
  {
    if (size_ != other.size_)
    {
      return false;
    }
    for (size_t i = 0; i < size_; ++i)
    {
      if (data_[i] != other.data_[i])
      {
        return false;
      }
    }
    return true;
  }

  template< class T >
  bool Stack< T >::operator!=(const Stack& other) const
  {
    return !operator==(other);
  }

  template< class T >
  T* Stack< T >::copyData(const Stack& other)
  {
    if (!other.capacity_)
    {
      return nullptr;
    }
    T* newData = static_cast< T* >(operator new(other.capacity_ * sizeof(T)));
    size_t i = 0;
    try
    {
      for (; i < other.size_; ++i)
      {
        new (newData + i) T(other.data_[i]);
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
    return newData;
  }

  template< class T >
  void Stack< T >::resize()
  {
    if (!capacity_)
    {
      data_ = static_cast< T* >(operator new(minStackCapacity * sizeof(T)));
      capacity_ = minStackCapacity;
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
      for (; i < size_; ++i)
      {
        new (newData + i) T(std::move_if_noexcept(data_[i]));
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
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i].~T();
    }
    operator delete(data_);
    data_ = newData;
    capacity_ = newCapacity;
  }

  template< class T >
  size_t Stack< T >::getBiggerCapacity(size_t capacity) const noexcept
  {
    if (!capacity)
    {
      return minStackCapacity;
    }
    if (capacity > maxSize() / 2)
    {
      return capacity;
    }
    return capacity * 2;
  }
}

#endif


#ifndef STACK_HPP
#define STACK_HPP

#include <utility>

namespace rychkov
{
  template< class T >
  class Stack
  {
  public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

    Stack() noexcept;
    Stack(const Stack& rhs);
    Stack(Stack&& rhs) noexcept;
    ~Stack();
    Stack& operator=(const Stack& rhs);
    Stack& operator=(Stack&& rhs) noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    reference top();
    const_reference top() const;

    void push(const value_type& value);
    void push(value_type&& value);
    void pop();
    template< class... Args >
    reference emplace(Args&&... args);

    void reserve(size_type newCapacity);
    void swap(Stack& rhs) noexcept;
  private:
    size_type size_, capacity_;
    value_type* data_;
  };
}

template< class T >
rychkov::Stack< T >::Stack() noexcept:
  size_(0),
  capacity_(0),
  data_(nullptr)
{}
template< class T >
rychkov::Stack< T >::Stack(const Stack& rhs):
  size_(0),
  capacity_(rhs.capacity_),
  data_(new value_type[rhs.capacity_])
{
  for (size_type i = 0; i < rhs.size_; i++)
  {
    push(rhs.data_[i]);
  }
}
template< class T >
rychkov::Stack< T >::Stack(Stack&& rhs) noexcept:
  size_(std::exchange(rhs.size_, 0)),
  capacity_(std::exchange(rhs.capacity_, 0)),
  data_(std::exchange(rhs.data_, nullptr))
{}
template< class T >
rychkov::Stack< T >::~Stack()
{
  while (!empty())
  {
    pop();
  }
  delete[] data_;
}
template< class T >
rychkov::Stack< T >& rychkov::Stack< T >::operator=(const Stack& rhs)
{
  Stack temp(rhs);
  swap(temp);
  return *this;
}
template< class T >
rychkov::Stack< T >& rychkov::Stack< T >::operator=(Stack&& rhs) noexcept
{
  Stack temp(std::move(*this));
  swap(rhs);
  return *this;
}

template< class T >
bool rychkov::Stack< T >::empty() const noexcept
{
  return size_ == 0;
}
template< class T >
typename rychkov::Stack< T >::size_type rychkov::Stack< T >::size() const noexcept
{
  return size_;
}
template< class T >
typename rychkov::Stack< T >::size_type rychkov::Stack< T >::capacity() const noexcept
{
  return capacity_;
}
template< class T >
typename rychkov::Stack< T >::reference rychkov::Stack< T >::top()
{
  return data_[size_ - 1];
}
template< class T >
typename rychkov::Stack< T >::const_reference rychkov::Stack< T >::top() const
{
  return data_[size_ - 1];
}
template< class T >
void rychkov::Stack< T >::pop()
{
  data_[--size_].~value_type();
}
template< class T >
void rychkov::Stack< T >::push(const value_type& value)
{
  emplace(value);
}
template< class T >
void rychkov::Stack< T >::push(value_type&& value)
{
  emplace(std::move(value));
}
template< class T >
template< class... Args >
typename rychkov::Stack< T >::reference rychkov::Stack< T >::emplace(Args&&... args)
{
  if (size_ >= capacity_)
  {
    reserve(size_ * 2 + 1);
  }
  new (data_ + size_) value_type(args...);
  return data_[size_++];
}
template< class T >
void rychkov::Stack< T >::swap(Stack& rhs) noexcept
{
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(data_, rhs.data_);
}
template< class T >
void rychkov::Stack< T >::reserve(size_type newCapacity)
{
  if (capacity_ >= newCapacity)
  {
    return;
  }
  Stack temp;
  temp.capacity_ = newCapacity;
  temp.data_ = new value_type[newCapacity];
  for (size_type i = 0; i < size_; i++)
  {
    temp.push(std::move_if_noexcept(data_[i]));
  }
  swap(temp);
}

#endif

#ifndef STACK_HPP
#define STACK_HPP

#include <utility>

namespace rychkov
{
  template< class T >
  class Queue
  {
  public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

    Queue() noexcept;
    Queue(const Queue& rhs);
    Queue(Queue&& rhs) noexcept;
    ~Queue();
    Queue& operator=(const Queue& rhs);
    Queue& operator=(Queue&& rhs) noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    void push(const value_type& value);
    void push(value_type&& value);
    void pop();
    template< class... Args >
    reference emplace(Args&&... args);

    void reserve(size_type newCapacity);
    void swap(Queue& rhs) noexcept;
  private:
    size_type size_, capacity_, head_;
    value_type* data_;

    size_type getLocalId(size_type globalId) const noexcept;
    reference operator[](size_type i);
    const_reference operator[](size_type i) const;
  };
}

template< class T >
rychkov::Queue< T >::Queue() noexcept:
  size_(0),
  capacity_(0),
  head_(0),
  data_(nullptr)
{}
template< class T >
rychkov::Queue< T >::Queue(const Queue& rhs):
  size_(0),
  capacity_(rhs.capacity_),
  head_(0),
  data_(new value_type[rhs.capacity_])
{
  for (size_type i = 0; i < rhs.size_; i++)
  {
    push(rhs[i]);
  }
}
template< class T >
rychkov::Queue< T >::Queue(Queue&& rhs) noexcept:
  size_(std::exchange(rhs.size_, 0)),
  capacity_(std::exchange(rhs.capacity_, 0)),
  head_(rhs.head_),
  data_(std::exchange(rhs.data_, nullptr))
{}
template< class T >
rychkov::Queue< T >::~Queue()
{
  while (!empty())
  {
    pop();
  }
  delete[] data_;
}
template< class T >
rychkov::Queue< T >& rychkov::Queue< T >::operator=(const Queue& rhs)
{
  Queue temp(rhs);
  swap(temp);
  return *this;
}
template< class T >
rychkov::Queue< T >& rychkov::Queue< T >::operator=(Queue&& rhs) noexcept
{
  Queue temp(std::move(*this));
  swap(rhs);
  return *this;
}

template< class T >
bool rychkov::Queue< T >::empty() const noexcept
{
  return size_ == 0;
}
template< class T >
typename rychkov::Queue< T >::size_type rychkov::Queue< T >::size() const noexcept
{
  return size_;
}
template< class T >
typename rychkov::Queue< T >::size_type rychkov::Queue< T >::capacity() const noexcept
{
  return capacity_;
}
template< class T >
typename rychkov::Queue< T >::reference rychkov::Queue< T >::front()
{
  return operator[](0);
}
template< class T >
typename rychkov::Queue< T >::const_reference rychkov::Queue< T >::front() const
{
  return operator[](0);
}
template< class T >
typename rychkov::Queue< T >::reference rychkov::Queue< T >::back()
{
  return operator[](size_ - 1);
}
template< class T >
typename rychkov::Queue< T >::const_reference rychkov::Queue< T >::back() const
{
  return operator[](size_ - 1);
}
template< class T >
void rychkov::Queue< T >::pop()
{
  operator[](--size_).~value_type();
}
template< class T >
void rychkov::Queue< T >::push(const value_type& value)
{
  emplace(value);
}
template< class T >
void rychkov::Queue< T >::push(value_type&& value)
{
  emplace(std::move(value));
}
template< class T >
template< class... Args >
typename rychkov::Queue< T >::reference rychkov::Queue< T >::emplace(Args&&... args)
{
  if (size_ >= capacity_)
  {
    reserve(size_ * 2 + 1);
  }
  new (data_ + getLocalId(size_)) value_type(args...);
  return operator[](size_++);
}
template< class T >
void rychkov::Queue< T >::swap(Queue& rhs) noexcept
{
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
  std::swap(head_, rhs.head_);
  std::swap(data_, rhs.data_);
}
template< class T >
void rychkov::Queue< T >::reserve(size_type newCapacity)
{
  if (capacity_ >= newCapacity)
  {
    return;
  }
  Queue temp;
  temp.capacity_ = newCapacity;
  temp.data_ = new value_type[newCapacity];
  for (size_type i = 0; i < size_; i++)
  {
    temp.push(std::move_if_noexcept(operator[](i)));
  }
  swap(temp);
}
template< class T >
typename rychkov::Queue< T >::size_type rychkov::Queue< T >::getLocalId(size_type globalId) const noexcept
{
  globalId += head_;
  return (globalId < capacity_ ? globalId : globalId - capacity_);
}
template< class T >
typename rychkov::Queue< T >::reference rychkov::Queue< T >::operator[](size_type i)
{
  return data_[getLocalId(i)];
}
template< class T >
typename rychkov::Queue< T >::const_reference rychkov::Queue< T >::operator[](size_type i) const
{
  return data_[getLocalId(i)];
}
#endif

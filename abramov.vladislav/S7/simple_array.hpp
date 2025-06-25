#ifndef SIMPLE_ARRAY_HPP
#define SIMPLE_ARRAY_HPP
#include <cstddef>

namespace abramov
{
  template< class T >
  struct SimpleArray
  {
    SimpleArray();
    ~SimpleArray();
    T &operator[](size_t id) noexcept;
    const T &operator[](size_t id) const noexcept;
    void pushBack(const T &val);
    size_t size() const noexcept;
  private:
    T *data_;
    size_t capacity_;
    size_t size_;

    void resize(size_t k);
  };
}

template< class T >
abramov::SimpleArray< T >::SimpleArray():
  data_(nullptr),
  capacity_(0),
  size_(0)
{}

template< class T >
abramov::SimpleArray< T >::~SimpleArray()
{
  delete[] data_;
}

template< class T >
const T &abramov::SimpleArray< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
T &abramov::SimpleArray< T >::operator[](size_t id) noexcept
{
  return const_cast< T& >(static_cast< const SimpleArray& >(*this)[id]);
}

template< class T >
void abramov::SimpleArray< T >::pushBack(const T &val)
{
  if (size_ >= capacity_)
  {
    if (capacity_)
    {
      capacity_ *= 2;
    }
    else
    {
      capacity_ = 10;
    }
    resize(capacity_);
  }
  data_[size_++] = val;
}

template< class T >
void abramov::SimpleArray< T >::resize(size_t k)
{
  T *new_data = new T[k];
  for (size_t i = 0; i < size_; ++i)
  {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
}

template< class T >
size_t abramov::SimpleArray< T >::size() const noexcept
{
  return size_;
}
#endif

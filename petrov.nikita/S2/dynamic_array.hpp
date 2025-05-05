#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace petrov
{
  template< typename T >
  struct DynamicArray
  {
  public:
    using this_t = DynamicArray< T >;
    DynamicArray():
      massive_(nullptr),
      capacity_(0),
      size_(0)
    {}
    DynamicArray(const this_t & rhs);
    DynamicArray(this_t && rhs);
    ~DynamicArray();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
    T & operator[](const size_t & pos);
    template< typename U >
    void push_back(U && val);
    void pop();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void swap(this_t & rhs) noexcept;
  private:
    T * massive_;
    size_t capacity_;
    size_t size_;
  };

  template< typename T >
  DynamicArray< T >::DynamicArray(const this_t & rhs):
    massive_(nullptr),
    capacity_(rhs.capacity_),
    size_(rhs.size_)
  {
    massive_ = new T[rhs.capacity_];
    for (size_t i = 0; i < rhs.size_; i++)
    {
      massive_[i] = rhs.massive_[i];
    }
  }

  template< typename T >
  DynamicArray< T >::DynamicArray(this_t && rhs):
    massive_(rhs.massive_),
    capacity_(rhs.capacity_),
    size_(rhs.size_)
  {}

  template< typename T >
  DynamicArray< T >::~DynamicArray()
  {
    delete[] massive_;
  }

  template< typename T >
  typename DynamicArray< T >::this_t & DynamicArray< T >::operator=(const this_t & rhs)
  {
    DynamicArray cpy(rhs);
    swap(cpy);
    return *this;
  }

  template< typename T >
  typename DynamicArray< T >::this_t & DynamicArray< T >::operator=(this_t && rhs)
  {
    delete[] massive_;
    massive_ = rhs.massive_;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    return *this;
  }

  template< typename T >
  T & DynamicArray< T >::operator[](const size_t & pos)
  {
    return massive_[pos];
  }

  template< typename T >
  template< typename U >
  void DynamicArray< T >::push_back(U && val)
  {
    if (empty())
    {
      delete[] massive_;
      capacity_ = 5;
      massive_ = new T[capacity_];
      massive_[size_++] = val;
    }
    else if (size_ == capacity_)
    {
      T * temp = new T[capacity_ *= 2];
      size_t i = 0;
      while (i < size_)
      {
        temp[i] = massive_[i];
        ++i;
      }
      delete[] massive_;
      massive_ = temp;
      massive_[i] = val;
      size_++;
    }
    else
    {
      massive_[size_++] = val;
    }
  }

  template< typename T >
  void DynamicArray< T >::pop()
  {
    if (empty())
    {
      return;
    }
    size_--;
  }

  template< typename T >
  T & DynamicArray< T >::front()
  {
    if (empty())
    {
      throw std::logic_error("ERROR: Array is empty");
    }
    return massive_[0];
  }

  template< typename T >
  const T & DynamicArray< T >::front() const
  {
    if (empty())
    {
      throw std::logic_error("ERROR: Array is empty");
    }
    return massive_[0];
  }

  template< typename T >
  T & DynamicArray< T >::back()
  {
    if (empty())
    {
      throw std::logic_error("ERROR: Array is empty");
    }
    return massive_[size_ - 1];
  }

  template< typename T >
  const T & DynamicArray< T >::back() const
  {
    if (empty())
    {
      throw std::logic_error("ERROR: Array is empty");
    }
    return massive_[size_ - 1];
  }

  template< typename T >
  bool DynamicArray< T >::empty() const noexcept
  {
    return !size_;
  }

  template< typename T >
  size_t DynamicArray< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  void DynamicArray< T >::swap(this_t & rhs) noexcept
  {
    std::swap(massive_, rhs.massive_);
    std::swap(capacity_, rhs.capacity_);
    std::swap(size_, rhs.size_);
  }
}


#endif

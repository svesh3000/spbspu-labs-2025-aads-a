#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <cassert>

namespace alymova
{
  template< typename T >
  struct Array
  {
    Array();
    Array(const Array< T >& other);
    Array(Array< T >&& other);
    ~Array();

    Array& operator=(const Array< T >& other);
    Array& operator=(Array< T >&& other);

    size_t size() const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_front();
    void pop_back();
    template< typename... Args >
    void emplace_back(Args&&... args);
  private:
    size_t size_;
    size_t capacity_;
    T* array_;
    T* begin_;
    T* size_ptr_;
    T* capacity_ptr_;

    void clear();
  };

  template< typename T >
  Array< T >::Array():
    size_(0),
    capacity_(10),
    array_(new T[capacity_]{}), //exp
    begin_(array_),
    size_ptr_(array_),
    capacity_ptr_(array_ + capacity_ - 1)
  {}

  template< typename T >
  Array< T >::Array(const Array< T >& other):
    size_(other.size_),
    capacity_(other.capacity_),
    array_(new T[capacity_]{}), //exp
    begin_(array_),
    size_ptr_(array_),
    capacity_ptr_(array_ + capacity_ - 1)
  {
    try
    {
      for (size_t i = 0; i < size_; i++)
      {
        array_[i] = other.array_[i]; //exp
        size_++;
        size_ptr_++;
      }
    }
    catch(const std::exception& e)
    {
      clear();
      throw; //exp
    }
  }

  template< typename T >
  Array< T >::Array(Array< T >&& other):
    size_(std::exchange(other.size_, 0)),
    capacity_(std::exchange(other.capacity_, 10)),
    array_(std::exchange(other.array_, nullptr)),
    begin_(std::exchange(other.begin_, nullptr)),
    size_ptr_(std::exchange(other.size_ptr_, nullptr)),
    capacity_ptr_(std::exchange(other.capacity_ptr_, nullptr))
  {}

  template< typename T >
  Array< T >::~Array()
  {
    clear();
  }

  template< typename T >
  Array< T >& Array< T >::operator=(const Array< T >& other)
  {
    Array copy(other); //exp
    std::swap(size_, copy.size_);
    std::swap(capacity_, copy.capacity_);
    std::swap(array_, copy.array_);
    std::swap(begin_, copy.begin_);
    std::swap(size_ptr_, copy.size_ptr_);
    std::swap(capacity_ptr_, copy.capacity_ptr_);
    return *this;
  }

  template< typename T >
  Array< T >& Array< T >::operator=(Array< T >&& other)
  {
    clear();
    size_ = std::exchange(other.size_, 0);
    capacity_ = std::exchange(other.capacity_, 10);
    array_ = std::exchange(other.array_, nullptr);
    begin_ = std::exchange(other.begin_, nullptr);
    size_ptr_ = std::exchange(other.size_ptr_, nullptr);
    capacity_ptr_ = std::exchange(other.capacity_ptr_, nullptr);
    return *this;
  }

  template< typename T >
  size_t Array< T >::size() const
  {
    return size_;
  }

  template< typename T >
  T& Array< T >::front()
  {
    assert(size_ != 0);
    return *begin_;
  }

  template< typename T >
  const T& Array< T >::front() const
  {
    assert(size_ != 0);
    return *begin_;
  }

  template< typename T >
  T& Array< T >::back()
  {
    assert(size_ != 0);
    return *(size_ptr_ - 1);
  }

  template< typename T >
  const T& Array< T >::back() const
  {
    assert(size_ != 0);
    return *(size_ptr_ - 1);
  }

  template< typename T >
  void Array< T >::push_back(const T& value)
  {
    emplace_back(value);
  }

  template< typename T >
  void Array< T >::push_back(T&& value)
  {
    emplace_back(std::forward< T >(value));
  }

  template< typename T >
  void Array< T >::pop_front()
  {
    assert(size_ != 0);
    begin_++;
    size_--;
  }

  template< typename T >
  void Array< T >::pop_back()
  {
    assert(size_ != 0);
    size_ptr_--;
    size_--;
  }

  template< typename T >
  template< typename... Args >
  void Array< T >::emplace_back(Args&&... args)
  {
    if ((size_ptr_ - 1) == capacity_ptr_)
    {
      size_ptr_ = array_;
    }
    if (size_ptr_ == begin_ && size_ != 0)
    {
      int ratio = 2;
      T* array_new = new T[capacity_ * 2]{};
      size_t i = 0;
      for (T* ptr = begin_; ptr != capacity_ptr_; ptr++)
      {
        array_new[i] = *ptr;
        i++;
      }
      array_new[i] = *capacity_ptr_;
      i++;
      for (T* ptr = array_; ptr != begin_; ptr++)
      {
        array_new[i] = *ptr;
        i++;
      }
      clear();
      capacity_ *= ratio;
      array_ = array_new;
      begin_ = array_;
      size_ptr_ = array_ + size_;
      capacity_ptr_ = array_ + capacity_ - 1;
    }
    *size_ptr_ = T{std::forward< Args >(args)...};
    size_ptr_++;
    size_++;
  }

  template< typename T >
  void Array< T >::clear()
  {
    delete[] array_;
  }

  /*template< typename T >
  Array< T >::Array():
    size_(0),
    capacity_(10),
    array_(new T[capacity_]) //exp
  {}

  template< typename T >
  Array< T >::Array(const Array< T >& other):
    size_(other.size_),
    capacity_(other.capacity_),
    array_(new T[capacity_]) //exp
  {
    try
    {
      for (size_t i = 0; i < size_; i++)
      {
        array_[i] = other.array_[i]; //exp
      }
    }
    catch(const std::exception& e)
    {
      clear();
      throw; //exp
    }
  }

  template< typename T >
  Array< T >::Array(Array< T >&& other):
    size_(std::exchange(other.size_, 0)),
    capacity_(std::exchange(other.capacity_, 10)),
    array_(std::exchange(other.array_, nullptr))
  {}

  template< typename T >
  Array< T >::~Array()
  {
    clear();
  }

  template< typename T >
  Array< T >& Array< T >::operator=(const Array< T >& other)
  {
    Array copy(other); //exp
    std::swap(size_, copy.size_);
    std::swap(capacity_, copy.capacity_);
    std::swap(array_, copy.array_);
    return *this;
  }

  template< typename T >
  Array< T >& Array< T >::operator=(Array< T >&& other)
  {
    clear();
    size_ = std::exchange(other.size_, 0);
    capacity_ = std::exchange(other.capacity_, 10);
    array_ = std::exchange(other.array_, nullptr);
    return *this;
  }

  template< typename T >
  size_t Array< T >::size() const
  {
    return size_;
  }

  template< typename T >
  T& Array< T >::front()
  {
    assert(size_ != 0);
    return array_[0];
  }

  template< typename T >
  const T& Array< T >::front() const
  {
    assert(size_ != 0);
    return array_[0];
  }

  template< typename T >
  T& Array< T >::back()
  {
    assert(size_ != 0);
    return array_[size_ - 1];
  }

  template< typename T >
  const T& Array< T >::back() const
  {
    assert(size_ != 0);
    return array_[size_ - 1];
  }

  template< typename T >
  void Array< T >::push_back(const T& value)
  {
    emplace(value);
  }

  template< typename T >
  void Array< T >::push_back(T&& value)
  {
    emplace(std::forward< T >(value));
  }

  template< typename T >
  void Array< T >::pop_front()
  {
    assert(size_ != 0);
    for (size_t i = 0; i < size_ - 1; i++)
    {
      array_[i] = array_[i + 1]; //exp
    }
    size_--;
  }

  template< typename T >
  void Array< T >::pop_back()
  {
    assert(size_ != 0);
    size_--;
  }

  template< typename T >
  template< typename... Args >
  void Array< T >::emplace(Args&&... args)
  {
    if (size_ == capacity_)
    {
      int ratio = 2;
      T* array_new = new T[capacity_ * ratio];
      for (size_t i = 0; i < size_; i++)
      {
        array_new[i] = array_[i];
      }
      clear();
      array_ = array_new;
      capacity_ *= ratio;
    }
    array_[size_] = T{std::forward< Args >(args)...};
    size_++;
  }

  template< typename T >
  void Array< T >::clear()
  {
    delete[] array_;
  }*/
}
#endif

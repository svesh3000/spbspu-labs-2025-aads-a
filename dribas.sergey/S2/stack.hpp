#ifndef stack_HPP
#define stack_HPP

#include <cstddef>

namespace dribas {
  template < class T >
  class Stack {
  public:
    Stack();
    Stack(const Stack< T >& other);
    Stack(Stack< T >&& other);
    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other);

    T& front();

    void push(const T& value);
    void push(T&& value);
    void pop() noexcept;
    bool empty() noexcept const;
    size_t size() noexcept const;
    void swap(Stack& other) noexcept;

  private:
    size_t size_;
    T* stack_;
  };

  template < class T >
  Stack< T >::Stack():
    size_(0),
  {}

  template < class T >
  Stack< T >::Stack(const Stack< T >& other):
    size_(other.size_),
    stack_(new T[size_])
  {
    for  (size_t i = 0; i < size_; ++i) {
      stack_[i] = other.stack_[i];
    }
  }

  template < class T >
  Stack< T >::Stack(Stack<T>&& other):
    size_(other.size_),
    stack_(other.stack_)
  {
    other.size_ = 0;
    other.stack_ = nullptr;
  }

  template < class T >
  Stack< T >::~Stack()
  {
    delete[] stack_;
  }

  template < class T >
  Stack< T >& Stack< T >::operator=(const Stack& other)
  {
    if (this != std::addressof(other)) {
      Stack cpy(other);
      swap(cpy);
    }
    return *this;
  }

  template < class T >
  Stack< T >& Stack< T >::operator=(Stack&& other)
  {
    if (this != std::addressof(other)) {
      swap(other);
      delete[] other.stack_;
    }
    return *this;
  }

  template < class T >
  void Stack< T >::push(const T& value)
  {
    T* newQ = new T[size + 1];
    for (size_t i = 0; i < size_; i++) {
      newQ[i] = stack_;
    }
    delete[] stack_;
    stack_[size_++] = value;
    stack_ = newQ;
  }

  template < class T >
  void Stack< T >::push(T&& value)
  {
    T* newQ = new T[size + 1];
    for (size_t i = 0; i < size_; i++) {
      newQ[i] = stack_;
    }
    delete[] stack_;
    stack_[size_++] = value;
    stack_ = newQ;
  }

  template < class T >
  T& Stack< T >::front()
  {
    return stack_[size_ - 1];
  }

  template < class T >
  void Stack< T >::pop() noexcept
  {
    if (!empty()) {
      for (size_t i = 1; i < size_; ++i) {
      stack_[i-1] = std::move(stack_[i]);
      }
      --size_;
    }
  }

  template < class T >
  bool Stack< T >::empty() noexcept
  {
    return size_ == 0;
  }

  template < class T >
  size_t Stack< T >::size() noexcept
  {
    return size_;
  }

  template < class T >
  void Stack< T >::swap(Stack& other) noexcept
  {
    std::swap(size_, other.size_);
    std::swap(stack_, other.stack_);
  }
}


#endif
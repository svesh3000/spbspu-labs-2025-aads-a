#ifndef STACK_HPP
#define STACK_HPP
#include <utility>
#include <stdexcept>
namespace kiselev
{
  template< typename T >
  class Stack
  {
  public:

    Stack();
    Stack(const Stack< T >&);
    Stack(Stack< T >&&);
    ~Stack();

    Stack< T >& operator=(const Stack< T >&);
    Stack< T >& operator=(Stack< T >&&);

    T& back();
    void pop();
    void push(T);

    size_t size();
    bool empty();

  private:
    T* arr_;
    size_t capacity_;
    size_t size_;

    void reallocate();
    void swap(Stack< T >&);
  };

  template< typename T >
  void Stack< T >::reallocate()
  {
    size_t newCapacity = capacity_ * 2;
    T* newArr = new T[newCapacity];
    for (size_t i = 0; i < size_; ++i)
    {
      newArr[i] = arr_[i];
    }
    delete[] arr_;
    capacity_ = newCapacity;
    arr_ = newArr;
  }

  template< typename T >
  void Stack< T >::swap(Stack< T >& stack)
  {
    std::swap(arr_, stack.arr_);
    std::swap(capacity_, stack.capacity_);
    std::swap(size_, stack.size_);
  }

  template< typename T >
  Stack< T >::Stack():
    arr_(nullptr),
    capacity_(5),
    size_(0)
  {
    arr_ = new T[capacity_];
  }

  template< typename T >
  Stack< T >::Stack(const Stack< T >& stack):
    arr_(nullptr),
    capacity_(stack.capacity_),
    size_(stack.size_)
  {
    arr_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i)
    {
      arr_[i] = stack[i];
    }
  }

  template< typename T >
  Stack< T >::Stack(Stack< T >&& stack):
    arr_(std::exchange(stack.arr_, nullptr)),
    capacity_(std::exchange(stack.capacity_, 0)),
    size_(std::exchange(stack.size_, 0))
  {}

  template< typename T >
  Stack< T >::~Stack()
  {
    delete[] arr_;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(const Stack< T >& stack)
  {
    Stack< T > copy(stack);
    swap(copy);
    return *this;
  }

  template< typename T >
  Stack< T >& Stack< T >::operator=(Stack< T >&& stack)
  {
    Stack< T > temp(std::move(stack));
    swap(temp);
    return *this;
  }

  template< typename T >
  T& Stack< T >::back()
  {
    if (empty())
    {
      throw std::logic_error("Stack is empty for back()");
    }
    return arr_[size_ - 1];
  }

  template< typename T >
  void Stack< T >::pop()
  {
    if (empty())
    {
      throw std::logic_error("Stack is empty for pop()");
    }
    --size_;
  }

  template< typename T >
  void Stack< T >::push(T data)
  {
    if (size_ >= capacity_)
    {
      reallocate();
    }
    arr_[size_] = data;
  }

  template< typename T >
  size_t Stack< T >::size()
  {
    return size_;
  }

  template< typename T >
  bool Stack< T >::empty()
  {
    return size_ == 0;
  }

}
#endif

#ifndef STACK_HPP
#define STACK_HPP

namespace maslov
{
  template< typename T >
  struct Stack
  {
    Stack();
    Stack(const Stack< T > & rhs);
    Stack(Stack< T > && rhs);
    ~Stack();

    Stack< T > & operator=(Stack< T > && rhs) noexcept;
    Stack< T > & operator=(const Stack< T > & rhs) noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void push(const T & data);
    void pop();

    T & top();
    const T & top() const;

    void swap(Stack< T > & rhs) noexcept;
   privite:
    size_t capacity_;
    size_t size_;
    T * data_;
  };
}

#endif
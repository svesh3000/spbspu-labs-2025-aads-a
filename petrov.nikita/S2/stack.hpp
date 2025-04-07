#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

namespace petrov
{
  template< typename T >
  struct Stack
  {
  public:
    using this_t = Stack< T >;
    Stack(): 
      massive_(nullptr), 
      size_of_stack(0)
    {}
    Stack(const this_t & rhs);
    Stack(this_t && rhs);
    ~Stack();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
    void push(const T & element);
    void pop();
    T & top();
    const T & top() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void swap(this_t & rhs) noexcept;
  private:
    T * massive_;
    size_t size_of_stack;
  };
}

#endif
#ifndef STACK_HPP
#define STACK_HPP

#include <algorithm>
#include <stdexcept>

namespace zholobov {

  template < typename T >
  class Stack {
  public:
    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;
    void push(const T& rhs);
    void push(T&& rhs);
    T top() const;
    void pop();
    bool empty() const;
  };
}

#endif

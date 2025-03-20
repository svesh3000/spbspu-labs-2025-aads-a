#ifndef STACK_HPP
#define STACK_HPP

#include <algorithm>
#include <stdexcept>

namespace zholobov {

  template < typename T >
  class Stack {
  public:
    Stack() {}
    Stack(const Stack& other) {}
    Stack(Stack&& other) noexcept {}
    Stack& operator=(const Stack& other) { return *this; }
    Stack& operator=(Stack&& other) noexcept { return *this; }
    void push(const T& rhs) {}
    void push(T&& rhs) {}
    const T& top() const { return T(); }
    T& top() { return T(); }
    void pop() {}
    bool empty() const { return true; }
  };
}

#endif

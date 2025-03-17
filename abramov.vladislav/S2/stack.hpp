#ifndef STACK_HPP
#define STACK_HPP
#include <cstddef>

namespace abramov
{
  template< class T >
  struct Stack
  {
    void push(const T &rhs);
    T &top();
    const T &top() const;
    void pop();
    size_t size() const;
    bool empty() const;
    void swap() noexcept;
  private:
    T *data_;
    size_t size_;
  };
}
#endif

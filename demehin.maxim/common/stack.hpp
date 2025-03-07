#ifndef STACK_HPP
#define STACK_HPP

namespace demehin
{
  template< typename T >
  class Stack
  {
  public:

    Stack();
    ~Stack();

    void push(T rhs);
    T drop();

  private:
    T* data_;
    size_t size_;
    size_t capacity_;
    bool isEmpty_;
  };

}

#endif

#ifndef STACK_HPP
#define STACK_HPP

namespace gavrilova {
  template < class T >
  class Stack {
  public:
    Stack();
    ~Stack();
    
    Stack& operator=(const Stack& other );
    Stack& operator=(Stack&& other );

    void push(const T& value);
    void push(T&& value);

    T& top();
    void pop();
    bool empty() const;
    size_t size() const;
    void swap( stack& other ) noexcept;

  private:
    T* stack_;
    size_t size_;
    size_t capacity;
  };
}
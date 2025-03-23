#ifndef STACK_HPP
#define STACK_HPP
template< typename T >
struct Stack
{
  Stack();
  Stack(const T& other);
  Stack(T&& other);
  ~Stack();

  bool empty() const;
  size_t size() const;
  T& top();
  const T& top() const;
  void push(const T& value);
  void push(T&& value);
  template< typename... Args >
  void emplace(Args&&... args);
  void pop();

private:
  T* array;
  size_t size;
  size_t capacity;
};
#endif

#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace demehin
{
  template< typename T >
  class Queue
  {
  public:

    Queue();
    ~Queue();

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

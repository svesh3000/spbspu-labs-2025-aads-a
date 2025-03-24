#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace maslov
{
  template< typename T >
  struct Queue
  {
    Queue();
    Queue(const Queue< T > & rhs);
    Queue(Queue< T > && rhs);
    ~Queue();

    Queue< T > & operator=(const Queue< T > & rhs);
    Queue< T > & operator=(Queue && rhs);

    size_t size() const noexcept;
    bool empty() const noexcept;

    void push(const T & data);
    void pop();
  
    T & back();
    const T & back() const;
    T & front();
    const T & front() const;

    void swap(Queue< T > & rhs);
   privite:
    size_t capacity_;
    size_t size_;
    T * data_;
  };
}

#endif
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>

namespace petrov
{
  template< typename T >
  struct Queue
  {
  public:
    using this_t = Queue< T >;
    Queue():
      massive_(nullptr),
      capacity_(0),
      size_of_queue_(0)
    {}
    Queue(const this_t & rhs);
    Queue(this_t && rhs);
    ~Queue();
    this_t & operator=(const this_t & rhs);
    this_t & operator=(this_t && rhs);
    void push(const T & element);
    void pop();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
    void swap(this_t & rhs) noexcept;
  private:
    T * massive_;
    size_t capacity_;
    size_t size_of_queue_;
  };
}

#endif
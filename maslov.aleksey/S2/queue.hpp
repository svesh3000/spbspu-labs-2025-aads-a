#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace maslov
{
  template< typename T >
  struct Queue
  {
    void push(const T & data);
    void pop();
    bool empty();
    T & front();
    const T & front() const;
  };
}

#endif
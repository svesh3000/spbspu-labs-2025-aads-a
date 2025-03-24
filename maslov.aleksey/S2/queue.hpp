#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace maslov
{
  template< typename T >
  struct Queue
  {
    void push(const T & data);
  };
}

#endif
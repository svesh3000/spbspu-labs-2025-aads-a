#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <algorithm>
#include <stdexcept>

namespace zholobov {

  template < typename T >
  class Queue {
  public:
    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
    void push(const T& rhs);
    void push(T&& rhs);
    T front() const;
    T back() const;
    void pop();
    bool empty() const;
  };

}

#endif

#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace gavrilova {
  template < class T >
  class Queue {
  public:
    Queue();
    ~Queue();
    
    Queue& operator=(const Queue& other );
    Queue& operator=(Queue&& other );

    void push(const T& value);
    void push(T&& value);

    T& front();
    T& back();
    void pop();
    bool empty() const;
    size_t size() const;
    void swap(Queue& other ) noexcept;

  private:
    T* stack_;
    size_t size_;
    size_t capacity;
  };
}

#endif
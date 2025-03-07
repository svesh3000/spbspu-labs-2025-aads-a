#ifndef FORWARD_RING_LIST_HPP
#define FORWARD_RING_LIST_HPP

#include <cstddef>

namespace petrov
{
  template< typename T >
  struct ForwardRingList
  {
  public:
  
    struct ForwardRingListIterator
    {
    public:
      using this_t = ForwardRingListIterator;
      ForwardRingListIterator();
      ForwardRingListIterator(const this_t & rhs) = default;
      ~ForwardRingListIterator() = default;
      this_t & operator=(const this_t & rhs) = default;
      this_t & operator++();
      this_t operator++(int);
      T & operator*();
      T * operator->();
      const T & operator*() const;
      const T * operator->() const;
      bool operator!=(const this_t &) const;
      bool operator==(const this_t &) const;
    private:
      ForwardRingList< T > * node;
    };

    using this_t = ForwardRingList< T >;
    using iterator_this_t = ForwardRingListIterator;
    ForwardRingList() = default;
    ForwardRingList(const this_t & rhs);
    ForwardRingList(this_t && rhs);
    ~ForwardRingList();
    this_t & operator=(const this_t & rhs);
    iterator_this_t begin();
    iterator_this_t end();
    T front();
    T back();
    bool empty() noexcept;
    size_t size() noexcept;
    void push_front();
    void push_back();
    void pop_front();
    void pop_back();
    void swap() noexcept;
    void clear();

  private:
    T data;
    ForwardRingList< T > * next;
  };
}

#endif
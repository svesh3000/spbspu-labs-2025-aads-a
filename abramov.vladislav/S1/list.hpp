#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include "node.hpp"

namespace abramov
{
  template< class T >
  struct List
  {
    List();
    ~List();
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    bool empty() const;
    size_t size() const;
  private:
    Node< T > *head_;
    Node< T > *tail_;
    size_t size_;
  };

  template< class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< class T >
  List< T >::~List()
  {
    while (head_)
    {
      Node< T > *temp = head_;
      head_ = head_->next_;
      delete temp;
    }
  }

  template< class T >
  T &List< T >::front()
  {
    return const_cast< T& >(const_cast< const List< T >* >(this)->front());
  }

  template< class T >
  const T &List< T >::front() const
  {
    return head_->data_;
  }

  template< class T >
  T &List< T >::back()
  {
    return const_cast< T& >(const_cast< const List< T >* >(this)->back());
  }

  template< class T >
  const T &List< T >::back() const
  {
    return tail_->data_;
  }

  template< class T >
  bool List< T >::empty() const
  {
    return size_ == 0;
  }

  template< class T >
  size_t List< T >::size() const
  {
    return size_;
  }
}
#endif

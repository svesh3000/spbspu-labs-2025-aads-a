#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <algorithm>
#include "node.hpp"
#include "iterator.hpp"
#include "cIterator.hpp"

namespace abramov
{
  template< class T >
  struct ConstIterator;

  template< class T >
  struct Iterator;

  template< class T >
  struct List
  {
    List();
    ~List();
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    void pushBack(const T &data);
    void pushFront(const T &data);
    void popBack();
    void popFront();
    void swap(List &rhs) noexcept;
    void clear();
    bool empty() const;
    size_t size() const;
    Iterator< T > begin() const;
    Iterator< T > end() const;
    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;
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
    clear();
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
  void List< T >::pushBack(const T &data)
  {
    Node< T > *node = new Node< T >{ data };
    if (empty())
    {
      head_ = node;
      tail_ = node;
    }
    else
    {
      tail_->next_ = node;
      node->prev_ = tail_;
      tail_ = node;
    }
    ++size_;
  }

  template< class T >
  void List< T >::pushFront(const T &data)
  {
    Node< T > *node = new Node< T >{ data };
    if (empty())
    {
      head_ = node;
      tail_ = node;
    }
    else
    {
      head_->prev_ = node;
      node->next_ = head_;
      head_ = node;
    }
    ++size_;
  }

  template< class T >
  void List< T >::popBack()
  {
    if (!empty())
    {
      --size_;
      if (head_ == tail_)
      {
        delete tail_;
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        Node< T > *node = tail_->prev_;
        delete tail_;
        tail_ = node;
        tail_->next_ = nullptr;
      }
    }
  }

  template< class T >
  void List< T >::popFront()
  {
    if (!empty())
    {
      --size_;
      if (head_ == tail_)
      {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        Node< T > *node = head_->next_;
        delete head_;
        head_ = node;
        head_->prev_ = nullptr;
      }
    }
  }

  template< class T >
  void List< T >::swap(List &rhs) noexcept
  {
    std::swap(head_, rhs.head_);
    std::swap(tail_, rhs.tail_);
    std::swap(size_, rhs.size_);
  }

  template< class T >
  void List< T >::clear()
  {
    while (head_)
    {
      Node< T > *temp = head_;
      head_ = head_->next_;
      delete temp;
    }
    size_ = 0;
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

  template< class T >
  Iterator< T > List< T >::begin() const
  {
    return Iterator< T >(head_);
  }

  template< class T >
  Iterator< T > List< T >::end() const
  {
    return Iterator< T >();
  }

  template< class T >
  ConstIterator< T > List< T >::cbegin() const
  {
    return ConstIterator< T >(head_);
  }

  template< class T >
  ConstIterator< T > List< T >::cend() const
  {
    return ConstIterator< T >();
  }
}
#endif

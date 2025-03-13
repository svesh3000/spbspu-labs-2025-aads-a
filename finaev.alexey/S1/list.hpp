#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>
#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

namespace finaev
{
  template <class T>
  struct List
  {
  public:
    List();
    List(const List<T>&);
    List< T >& operator=(const List<T>&);
    List(List&&) noexcept;
    List< T >& operator=(List<T>&&);
    void swap(List& other) noexcept;
    bool isEmpty() noexcept;
    void pushBack(const T& data);
    listIterator< T > begin();
    listIterator< T > end();
    constListIterator< T > constBegin() const;
    constListIterator< T > constEnd() const;
    T& front();
    T& back();
    size_t size() noexcept;
    void popFront();
    void clear();
    ~List();
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };

  template < class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template < class T >
  List< T >::List(const List< T >& other) :
    List()
  {
    for (constListIterator< T > i = other.constBegin(); i != other.constEnd(); ++i)
    {
      pushBack(*i);
    }
  }

  template < class T >
  void List< T >::swap(List& other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  template < class T >
  List< T >& List< T >::operator=(const List& other)
  {
    if (*this != other)
    {
      List< T > temp(other);
      swap(temp);
    }
    return *this;
  }

  template < class T >
  List< T >::List(List&& other) noexcept
  {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  template < class T >
  List< T >& List<T>::operator=(List< T >&& other)
  {
    if (*this != other)
    {
      List< T > temp = std::move(other);
      swap(temp);
    }
    return *this;
  }

  template < class T >
  void List< T >::pushBack(const T& data)
  {
    Node< T >* elem = new Node< T >(data);
    if (isEmpty())
    {
      head_ = elem;
      tail_ = elem;
    }
    else
    {
      tail_->next = elem;
      elem->prev = tail_;
      tail_ = elem;
    }
    ++size_;
  }

  template < class T >
  listIterator< T > List < T >::begin()
  {
    listIterator< T > res(head_);
    return res;
  }

  template < class T >
  listIterator< T > List < T >::end()
  {
    if (tail_ == nullptr)
    {
      listIterator< T > res;
      return res;
    }
    listIterator< T > res(tail_->next);
    return res;
  }

  template < class T >
  constListIterator< T > List< T >::constBegin() const
  {
    return constListIterator< T >(head_);
  }

  template < class T >
  constListIterator< T > List< T >::constEnd() const
  {
    if (tail_ == nullptr)
    {
      constListIterator< T > res;
      return res;
    }
    constListIterator< T > res(tail_->next);
    return res;
  }

  template < class T >
  bool List< T >::isEmpty() noexcept
  {
    return size_ == 0;
  }

  template < class T >
  size_t List< T >::size() noexcept
  {
    return size_;
  }

  template <typename T>
  void List<T>::popFront()
  {
    if (!isEmpty())
    {
      Node< T >* toDelete = head_;
      if (head_ != nullptr)
      {
        head_ = head_->next;
      }
      if (head_ != nullptr)
      {
        head_->prev = nullptr;
      }
      else
      {
        tail_ = nullptr;
      }
      delete toDelete;
      --size_;
    }
  }

  template < class T >
  void List< T >::clear()
  {
    while (!isEmpty())
    {
      popFront();
    }
  }

  template < class T >
  List< T >::~List()
  {
    clear();
  }
}

#endif

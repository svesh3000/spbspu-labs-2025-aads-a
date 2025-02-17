#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <stdexcept>
#include <type_traits>
#include "iterator.hpp"
#include "node.hpp"

namespace kiselev
{
  template< typename T>
  class List
  {
  public:

    List(): head_(nullptr), size_(0) {};
    List(const List< T >&);
    List(const List< T >&&);
    ~List();

    Iterator< T > begin() const noexcept;
    Iterator< T > end() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    T& front() const noexcept;
    T& back() const noexcept;

    void push_back(const T&);
    void push_front(const T&);

    void pop_back();
    void pop_front();

    void clear();
    void swap(List< T >&) noexcept;


  private:

    Node< T >* head_;
    size_t size_;

  };

  template< typename T>
  List< T >::List(const List< T >& list):
    List()
  {
    try
    {
      Iterator< T > it = list.begin();
      while(size() != list.size())
      {
        push_back(*it);
        ++it;
      }
    }
    catch(...)
    {
      clear();
    }
  }

  template< typename T >
  List< T >::List(const List< T >&& list):
    head_(list.head_),
    size_(list.size_)
  {
    list.head_ = nullptr;
    list.size_ = 0;
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
    delete head_;
  }

  template< typename T >
  Iterator< T > List< T >::begin() const noexcept
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  Iterator< T > List< T >::end() const noexcept
  {
    return Iterator< T >(head_->prev_);
  }

  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  size_t List< T >::size() const noexcept
  {
    return size_;
  }

  template< typename T >
  T& List< T >::front() const noexcept
  {
    return head_->data_;
  }

  template< typename T >
  T& List< T >::back() const noexcept
  {
    return head_->prev_->data_;
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    if (empty())
    {
      head_ = new Node< T >(data);
      head_->next_ = head_;
      head_->prev_ = head_;
    }
    else
    {
      Node< T >* newNode = new Node< T >(data);
      head_->prev_->next_ = newNode;
      newNode->prev_ = head_->prev_;
      newNode->next_ = head_;
      head_->prev_ = newNode;
    }
    ++size_;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    if (empty())
    {
      head_ = new Node< T >(data);
      head_->next_ = head_;
      head_->prev_ = head_;
    }
    else
    {
      Node< T >* newNode = new Node< T >(data);
      newNode->next_ = head_;
      newNode->prev_ = head_->prev_;
      head_->prev_->next_ = newNode;
      head_->prev_ = newNode;
      head_ = newNode;
    }
    ++size_;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    assert(!empty());
    if (size_ == 1)
    {
      delete head_;
      head_ = nullptr;
    }
    else
    {
      Node< T >* oldTail = head_->prev_;
      head_->prev_ = oldTail->prev_;
      head_->prev_->next_ = head_;
      delete oldTail;
    }
    --size_;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    assert(!empty());
    if (size_ == 1)
    {
      delete head_;
      head_ = nullptr;
    }
    else
    {
      Node< T >* oldHead = head_;
      head_ = head_->next_;
      head_->prev_->next_ = head_;
      delete oldHead;
    }
    --size_;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }

  template< typename T >
  void List< T >::swap(List<T>& list) noexcept
  {
    std::swap(head_, list.head_);
    std::swap(size_, list.size_);
  }

}
#endif

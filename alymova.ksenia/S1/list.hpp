#ifndef LIST_HPP
#define LIST_HPP
#include <cassert>
#include <iostream>
#include "iterators.hpp"
#include "listNode.hpp"

namespace alymova
{
  template< typename T >
  class List
  {
  public:
    List();
    List(const List< T >& other);
    List(List< T >&& other);
    List(size_t n, const T& value);
    ~List();

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other);

    Iterator< T > begin() noexcept;
    ConstIterator< T > begin() const noexcept;
    ConstIterator< T > cbegin() const noexcept;
    Iterator< T > end() noexcept;
    ConstIterator< T > end() const noexcept;
    ConstIterator< T > cend() const noexcept;

    T& front() noexcept;
    T& back() noexcept;
    const T& front() const noexcept;
    const T& back() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

    void push_front(const T& value);
    void pop_front() noexcept;
    void push_back(const T& value);
    void pop_back() noexcept;
    void swap(List< T >& other) noexcept;
    void clear() noexcept;
  private:
    ListNode< T >* fake_;
    ListNode< T >* head_;

    void do_null() noexcept;
  };
  template< typename T >
  bool operator==(const List< T >& lhs, const List< T >& rhs)
  {
    if (lhs.size() != rhs.size())
    {
      return false;
    }
    for (ConstIterator< T > it_lhs = lhs.cbegin(), it_rhs = rhs.cbegin(); it_lhs != lhs.cend(); ++it_lhs, ++it_rhs)
    {
      if ((*it_lhs) != (*it_rhs))
      {
        return false;
      }
    }
    return true;
  }
  template< typename T >
  bool operator!=(const List< T >& lhs, const List< T >& rhs)
  {
    return (!(lhs == rhs));
  }

  template< typename T >
  List< T >::List():
    fake_(new ListNode< T >(T(), nullptr, nullptr)),
    head_(fake_)
  {}
  template< typename T >
  List< T >::List(const List< T >& other):
    List()
  {
    try
    {
      for (ConstIterator< T > it = other.cbegin(); it != other.cend(); ++it)
      {
        push_back(*(it));
      }
    }
    catch (const std::bad_alloc& e)
    {
      clear();
      throw;
    }
  }
  template< typename T >
  List< T >::List(List< T >&& other):
    fake_(other.fake_),
    head_(other.head_)
  {
    other.do_null();
  }
  template< typename T >
  List< T >::List(size_t n, const T& value):
    List()
  {
    for (size_t i = 0; i < n; i++)
    {
      push_back(value);
    }
  }
  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    if (this != std::addressof(other))
    {
      List< T > copy(other);
      swap(copy);
    }
    return *this;
  }
  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other)
  {
    clear();
    fake_ = other.fake_;
    head_ = other.head_;
    other.do_null();
    return *this;
  }
  template< typename T >
  List< T >::~List()
  {
    clear();
  }
  template< typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }
  template< typename T >
  ConstIterator< T > List< T >::begin() const noexcept
  {
    return ConstIterator< T >(head_);
  }
  template< typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return begin();
  }
  template< typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >(fake_);
  }
  template< typename T >
  ConstIterator< T > List< T >::end() const noexcept
  {
    return ConstIterator< T >(fake_);
  }
  template< typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return end();
  }
  template< typename T >
  T& List< T >::front() noexcept
  {
    assert(!empty());
    return head_->data_;
  }
  template< typename T >
  T& List< T >::back() noexcept
  {
    assert(!empty());
    return fake_->prev_->data_;
  }
  template< typename T >
  const T& List< T >::front() const noexcept
  {
    assert(!empty());
    return head_->data_;
  }
  template< typename T >
  const T& List< T >::back() const noexcept
  {
    assert(!empty());
    return fake_->prev_->data_;
  }
  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return cbegin() == cend();
  }
  template< typename T >
  size_t List< T >::size() const noexcept
  {
    size_t size = 0;
    ConstIterator< T > it = begin();
    while (it != end())
    {
      ++it;
      ++size;
    }
    return size;
  }
  template< typename T >
  void List< T >::push_front(const T& value)
  {
    ListNode< T >* node = new ListNode< T >(value, nullptr, nullptr);
    if (empty())
    {
      head_ = node;
      head_->next_ = fake_;
      fake_->prev_ = head_;
    }
    else
    {
      ListNode< T >* subhead = head_;
      head_ = node;
      head_->next_ = subhead;
      subhead->prev_ = head_;
    }
  }
  template< typename T >
  void List< T >::pop_front() noexcept
  {
    assert(!empty());
    ListNode< T >* subhead = head_->next_;
    delete head_;
    head_ = subhead;
    head_->prev_ = nullptr;
  }
  template< typename T >
  void List< T >::push_back(const T& value)
  {
    ListNode< T >* node = new ListNode< T >(value, nullptr, nullptr);
    if (empty())
    {
      head_ = node;
      head_->next_ = fake_;
      fake_->prev_ = head_;
    }
    else
    {
      ListNode< T >* subhead = head_;
      for (Iterator< T > it = ++begin(); it != end(); ++it)
      {
        subhead = subhead->next_;
      }
      subhead->next_ = node;
      node->prev_ = subhead;
      node->next_ = fake_;
      fake_->prev_ = node;
    }
  }
  template< typename T >
  void List< T >::pop_back() noexcept
  {
    assert(!empty());
    ListNode< T >* subhead = head_;
    for (Iterator< T > it = ++begin(); it != end(); ++it)
    {
      subhead = subhead->next_;
    }
    if (size() == 1)
    {
      head_ = fake_;
      fake_->prev_ = nullptr;
      delete subhead;
    }
    else
    {
      subhead->prev_->next_ = fake_;
      fake_->prev_ = subhead->prev_;
      delete subhead;
    }
  }
  template< typename T >
  void List< T >::swap(List< T >& other) noexcept
  {
    std::swap(fake_, other.fake_);
    std::swap(head_, other.head_);
  }
  template< typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
    delete fake_;
  }
  template< typename T >
  void List< T >::do_null() noexcept
  {
    fake_ = nullptr;
    head_ = nullptr;
  }
}
#endif

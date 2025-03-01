#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"

namespace aleksandrov
{
  template< typename T>
  class List
  {
  public:
    List();
    ~List();

    Iterator< T > begin() const;
    T& front();
    bool empty();
    size_t size();

    void pushFront(const T& value);
    void popFront();
    void swap(List< T >& other);
    void clear() noexcept;

  private:
    Node< T >* fake_;
    Node< T >* tail_;
  };

  template< typename T >
  List< T >::List():
    fake_(new Node< T >()),
    tail_(fake_)
  {}

  template< typename T >
  List< T >::~List()
  {
    clear();
    delete fake_;
  }

  template< typename T >
  Iterator< T > List< T >::begin() const
  {
    return Iterator< T >(fake_->next_);
  }

  template< typename T >
  T& List< T >::front()
  {
    return *begin();
  }

  template< typename T >
  bool List< T >::empty()
  {
    return size() == 0;
  }

  template< typename T >
  size_t List< T >::size()
  {
    auto pos = fake_->next_;
    if (!pos)
    {
      return 0;
    }
    size_t size = 1;
    while (pos->next_ != tail_)
    {
      pos = pos->next_;
      ++size;
    }
    return size;
  }

  template< typename T >
  void List< T >::pushFront(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    newNode->next_ = fake_->next_;
    if (!empty())
    {
      fake_->next_ = newNode;
    }
    else
    {
      fake_->next_ = newNode;
      newNode->next_ = tail_;
    }
  }

  template< typename T >
  void List< T >::popFront()
  {
    if (!empty())
    {
      auto tempPtr = fake_->next_;
      fake_->next_ = tempPtr->next_;
      delete tempPtr;
    }
  }

  template< typename T >
  void List< T >::swap(List< T >& other)
  {
    std::swap(fake_, other.fake_);
    std::swap(tail_, other.tail_);
  }

  template< typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      popFront();
    }
  }
}

#endif


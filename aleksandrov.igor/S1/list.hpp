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
    List(size_t count, const T& value);
    List(const List< T >& rhs);
    List(List< T >&& rhs) noexcept;
    ~List();

    Iterator< T > begin() const;
    Iterator< T > end() const;
    T& front();
    T& back();
    bool empty();
    size_t size();

    void pushFront(const T& value);
    void pushBack(const T& value);
    void popFront();
    void popBack();
    void swap(List< T >& other);
    void clear() noexcept;

    void remove(const T& value);

    Iterator< T > insertAfter(Iterator< T > pos, const T& value);

  private:
    Node< T >* fake_;
    Node< T >* tail_;
  };

  template< typename T >
  List< T >::List():
    fake_(new Node< T >()),
    tail_(nullptr)
  {}

  template< typename T >
  List< T >::List(size_t count, const T& value):
    List()
  {
    for (size_t i = 0; i < count; ++i)
    {
      pushBack(value);
    }
  }

  template< typename T >
  List< T >::List(const List< T >& rhs):
    List()
  {
    for (auto it = rhs.begin(); it != rhs.end(); ++it)
    {
      pushBack(*it);
    }
  }

  template< typename T >
  List< T >::List(List< T >&& rhs) noexcept:
    fake_(rhs.fake_),
    tail_(rhs.tail_)
  {
    rhs.fake_ = new Node< T >();
    rhs.fake_->next = rhs.fake_;
    rhs.tail_ = nullptr;
  }

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
  Iterator< T > List< T >::end() const
  {
    return Iterator< T >(tail_);
  }

  template< typename T >
  T& List< T >::front()
  {
    return *begin();
  }

  template< typename T >
  T& List< T >::back()
  {
    return *end();
  }

  template< typename T >
  bool List< T >::empty()
  {
    return size() == 0;
  }

  template< typename T >
  size_t List< T >::size()
  {
    auto tempPtr = fake_->next_;
    if (!tempPtr)
    {
      return 0;
    }
    size_t size = 0;
    while (tempPtr != fake_)
    {
      ++size;
      tempPtr = tempPtr->next_;
    }
    return size;
  }

  template< typename T >
  void List< T >::pushFront(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    if (!empty())
    {
      newNode->next_ = fake_->next_;
      fake_->next_ = newNode;
    }
    else
    {
      newNode->next_ = fake_->next_;
      fake_->next_ = newNode;
      tail_ = newNode;
      newNode->next_ = fake_;
    }
  }

  template< typename T >
  void List< T >::pushBack(const T& value)
  {
    Node< T >* newNode = new Node< T >(value);
    newNode->next_ = fake_;
    if (!empty())
    {
      tail_->next_ = newNode;
    }
    else
    {
      fake_->next_ = newNode;
    }
    tail_ = newNode;
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


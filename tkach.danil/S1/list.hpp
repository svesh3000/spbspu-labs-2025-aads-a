#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "list_const_iterator.hpp"
#include "list_iterator.hpp"

namespace tkach
{
  template< typename T >
  class List
  {
  public:
    List();
    List(const List< T >& other);
    List(List< T >&& other);
    ~List();
    Iterator< T > begin() noexcept;
    Citerator< T > cbegin() const noexcept;
    Iterator< T > end() noexcept;
    Citerator< T > cend() const noexcept;
    bool empty() const noexcept;
    T& front();
    const T& front() const;
    size_t size() const;
    void pushFront(const T& data);
    void pushBack(const T& data);
    void pushFront(T&& data);
    void pushBack(T&& data);
    void popFront();
    void clear();
    void swap(List< T >& other) noexcept;
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
    List< T > getList(const List< T >& other);
  };

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(head_),
    size_(0)
  {}

  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  List< T > List< T >::getList(const List< T >& other)
  {
    List< T > temp;
    if (other.empty())
    {
      return temp;
    }
    try
    {
      temp.pushBack(*(other.cbegin()));
      for (auto it = ++other.cbegin(); it != other.cend(); ++it)
      {
        temp.pushBack(*it);
      }
    }
    catch (const std::bad_alloc&)
    {
      temp.clear();
      throw;
    }
    return temp;
  }

  template< typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  Citerator< T > List< T >::cbegin() const noexcept
  {
    return Citerator< T >(head_);
  }

  template< typename T >
  Citerator< T > List< T >::cend() const noexcept
  {
    return Citerator< T >(head_);
  }

  template< typename T >
  T& List< T >::front()
  {
    return const_cast< T& >(static_cast< const List< T >* >(this)->front());
  }
  
  template< typename T >
  const T& List< T >::front() const
  {
    return head_->data_;
  }

  template< typename T >
  size_t List< T >::size() const
  {
    return size_;
  }

  template< typename T >
  void List< T >::swap(List< T >& other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  template< typename T >
  void List< T >::pushFront(const T& data)
  {
    pushFront(T(data));
  }

  template< typename T >
  List< T >::List(const List< T >& other):
    List(getList(other))
  {}

  template< typename T >
  void List< T >::pushBack(const T& data)
  {
    pushBack(T(data));
  }

  template< typename T >
  void List< T >::pushFront(T&& data)
  {
    Node< T >* new_node = new Node< T >(std::move(data), head_);
    if (!head_)
    {
      head_ = new_node;
      head_->next_ = head_;
      tail_ = head_;
    }
    else
    {
      tail_->next_ = new_node;
      new_node->next_ = head_;
      head_ = new_node;
    }
    size_++;
  }

  template< typename T >
  void List< T >::pushBack(T&& data)
  {
    Node< T >* new_node = new Node< T >(std::move(data), head_);
    if (!head_)
    {
      head_ = new_node;
      head_->next_ = head_;
      tail_ = head_;
    }
    else
    {
      new_node->next_ = head_;
      tail_->next_ = new_node;
      tail_ = new_node;
    }
    size_++;
  }

  template< typename T >
  void List< T >::popFront()
  {
    if (empty())
    {
      return;
    }
    Node< T >* temp = head_;
    if (head_ == tail_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      tail_->next_ = head_->next_;
      head_ = head_->next_;
    }
    delete temp;
    size_--;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (head_)
    {
      popFront();
    }
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
  }

  template< typename T >
  List< T >::List(List< T >&& other):
    head_(other.head_),
    tail_(other.tail_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
}

#endif

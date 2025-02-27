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
    bool empty() const;
    T& front();
    size_t size();
    void push_front(const T& data);
    void push_back(const T& data);
    void push_front(T&& data);
    void push_back(T&& data);
    void pop_front();
    void clear();
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(head_),
    size_(0)
  {}

  template< typename T >
  bool List< T >::empty() const
  {
    return size_ == 0;
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
    return head_->data_;
  }

  template< typename T >
  size_t List< T >::size()
  {
    return size_;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    push_front(T(data));
  }

  template< typename T >
  List< T >::List(const List< T >& other):
    List()
  {
    if (other.empty())
    {
      return;
    }
    push_back(*(other.cbegin()));
    for (auto it = ++other.cbegin(); it != other.cend(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    push_back(T(data));
  }

  template< typename T >
  void List< T >::push_front(T&& data)
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
  void List< T >::push_back(T&& data)
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
  void List< T >::pop_front()
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
      pop_front();
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

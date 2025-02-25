#ifndef LIST_HPP
#define LIST_HPP

#include "cstddef"
#include "iterator.hpp"
#include "constIterator.hpp"

namespace mozhegova
{
  template< typename T >
  class List
  {
  public:
    List();
    List(const List< T > &);
    List(List< T > &&);
    List(size_t, const T &);
    ~List();

    Iterator< T > begin() const;
    Iterator< T > end() const;
    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    bool empty() const;
    size_t size() const;

    void push_front(const T &);
    void push_back(const T &);
    void pop_front();
    void pop_back();

    void clear();
    void swap(List< T > &);

    void remove(const T &);
    template< typename condition >
    void removeIf(condition);

    void splice(ConstIterator< T > pos, List< T > & x);
    void splice(ConstIterator< T > pos, List< T > && x);
    void splice(ConstIterator< T > pos, List< T > & x, ConstIterator< T > i);
    void splice(ConstIterator< T > pos, List< T > && x, ConstIterator< T > i);
    void splice(ConstIterator< T > pos, List< T > & x, ConstIterator< T > first, ConstIterator< T > last);
    void splice(ConstIterator< T > pos, List< T > && x, ConstIterator< T > first, ConstIterator< T > last);

    void assign(size_t, const T &);
  private:
    Node< T > * fake_;
    Node< T > * tail_;
    size_t size_;
  };

  template< typename T >
  List< T >::List():
    fake_(new Node< T >()),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  List< T >::List(const List< T > & rhs):
    List()
  {
    for (auto it = rhs.begin(); it != rhs.end(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  List< T >::List(List< T > && rhs):
    fake_(rhs.fake_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.fake_ = nullptr;
    rhs.tail_ = nullptr;
    rhs.size_ = 0;
  }

  template< typename T >
  List< T >::List(size_t n, const T & val):
    List()
  {
    assign(n, val);
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
    return Iterator< T >(tail_->next_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const
  {
    return Iterator< T >(fake_->next_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const
  {
    return Iterator< T >(tail_->next_);
  }

  template< typename T >
  T & List< T >::front()
  {
    return fake_->next_->data_;
  }

  template< typename T >
  const T & List< T >::front() const
  {
    return fake_->next_->data_;
  }

  template< typename T >
  T & List< T >::back()
  {
    return tail_->data_;
  }

  template< typename T >
  const T & List< T >::back() const
  {
    return tail_->data_;
  }

  template< typename T >
  bool List< T >::empty() const
  {
    return size_ == 0;
  }

  template< typename T >
  size_t List< T >::size() const
  {
    return size_;
  }

  template< typename T >
  void List< T >::push_front(const T & data)
  {
    Node< T > * newNode = new Node< T > (data);
    newNode->next_ = fake_->next_;
    if (size_ > 0)
    {
      fake_->next_->prev_ = newNode;
    }
    else
    {
      tail_ = newNode;
    }
    fake_->next_ = newNode;
    newNode->prev_ = fake_;
    size_++;
  }

  template< typename T >
  void List< T >::push_back(const T & data)
  {
    Node< T > * newNode = new Node< T > (data);
    if (size_ > 0)
    {
      newNode->prev_ = tail_;
      tail_->next_ = newNode;
    }
    else
    {
      newNode->prev_ = fake_;
      fake_->next_ = newNode;
    }
    tail_ = newNode;
    size_++;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    assert(!empty());
    Node< T > * tempNode = fake_->next_;
    fake_->next_ = tempNode->next_;
    if (fake_->next_ != nullptr)
    {
      tempNode->next_->prev_ = fake_;
    }
    delete tempNode;
    size_--;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    assert(!empty());
    Node< T > * tempNode = tail_;
    if (size_ == 1)
    {
      fake_->next_ = nullptr;
    }
    else
    {
      tail_ = tail_->prev_;
      tail_->next_ = nullptr;
    }
    delete tempNode;
    size_--;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  void List< T >::swap(List< T > & otherList)
  {
    std::swap(fake_->next_, otherList.fake_->next_);
    std::swap(tail_, otherList.tail_);
    std::swap(size_, otherList.size_);
  }

  template< typename T >
  void List< T >::remove(const T &)
  {
    for (auto it = this.begin(); it != this.end(); ++it)
    {
      if (*it == T)
      {
        erase(it);
      }
    }
  }

  template< typename T >
  template< typename condition >
  void List< T >::removeIf(condition c)
  {
    for (auto it = this.begin(); it != this.end(); ++it)
    {
      if (c(*it))
      {
        erase(it);
      }
    }
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T > & x)
  {
    
  }

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T > && x)
  {}

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T > & x, ConstIterator< T > i)
  {}

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T > && x, ConstIterator< T > i)
  {}

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T > & x, ConstIterator< T > first, ConstIterator< T > last)
  {}

  template< typename T >
  void List< T >::splice(ConstIterator< T > pos, List< T > && x, ConstIterator< T > first, ConstIterator< T > last)
  {}

  template< typename T >
  void List< T >::assign(size_t n, const T & val)
  {
    clear();
    for (size_t i = 0; i < n; i++)
    {
      push_back(val);
    }
  }
}

#endif

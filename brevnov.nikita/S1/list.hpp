#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include "iterator.hpp"
namespace brevnov
{
  template< typename T >
  class List
  {
  public:
    using Iter = Iterator< T, false >;
    using ConstIter = Iterator< T, true >;

    List();
    List(size_t n, const T& val);
    List(const List< T > & copy);
    List(List< T > && del);
    template< typename InputIterator >
    List(InputIterator begin, InputIterator end);
    List(std::initializer_list< T > il);
    ~List();

    List< T > & operator=(const List< T > & copy);
    List< T > & operator=(List< T > && copy);
    List< T > & operator=(std::initializer_list< T > il);

    Iter begin() noexcept;
    ConstIter cbegin() const noexcept;
    Iter end() noexcept;
    ConstIter cend() const noexcept;

    T& front() noexcept;
    const T& front() const noexcept;
    T& back() noexcept;
    const T& back() const noexcept;

    void push_back(const T&);
    void push_back(T&&);
    void push_front(const T&);
    void push_front(T&&);

    void pop_front() noexcept;
    void pop_back() noexcept;

    void clear();
    void swap(List< T > & hl);

    bool empty() const noexcept;
    size_t size() const noexcept;
  private:
    Node< T > * head_;
    Node< T > * tail_;
    size_t size_;
  };

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  List< T >::List(size_t n, const T& val):
    List()
  {
    for (size_t i = 0; i < n; i++)
    {
      push_back(val);
    }
  }

  template< typename T >
  List< T >::List(const List< T >& copy)
  {
    for (ConstIter it = copy.cbegin(); it != copy.cend(); ++it)
    {
      push_back(*it);
    }
  }

  template< typename T >
  List< T >::List(List< T > && del):
    head_(del.head_),
    tail_(del.tail_),
    size_(del.size_)
  {
    del.head_ = nullptr;
    del.tail_ = nullptr;
    del.size_ = 0;
  }

  template< typename T >
  template< typename InputIterator >
  List< T >::List(InputIterator begin, InputIterator end):
    List()
  {
    for (; begin != end; ++begin)
    {
      push_back(*begin);
    }
  }

  template< typename T >
  List< T >::List(std::initializer_list< T > il):
    List(il.begin(), il.end())
  {}

  template< typename T >
  List< T >::~List()
  {
    clear();
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
  List< T > & List< T >::operator=(const List< T > & copy)
  {
    List< T > cpy(copy);
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  void List< T >::swap(List< T > & hl)
  {
    std::swap(head_, hl.head_);
    std::swap(tail_, hl.tail_);
    std::swap(size_, hl.size_);
  }

  template< typename T >
  List< T > & List< T >::operator=(List< T > && copy)
  {
    List< T > cpy(std::move(copy));
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  List< T > & List< T >::operator=(std::initializer_list< T > il)
  {
    List< T > cpy(il);
    std::swap(cpy);
    return *this;
  }

  template< typename T >
  typename List< T >::Iter List< T >::begin() noexcept
  {
    return Iter(head_);
  }

  template< typename T >
  typename List< T >::ConstIter List< T >::cbegin() const noexcept
  {
    return ConstIter(head_);
  }

  template< typename T >
  typename List< T >::Iter List< T >::end() noexcept
  {
    return Iter(nullptr);
  }

  template< typename T >
  typename List< T >::ConstIter List< T >::cend() const noexcept
  {
    return ConstIter(nullptr);
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
  T& List< T >::front() noexcept
  {
    return head_->data;
  }

  template< typename T >
  const T& List< T >::front() const noexcept
  {
    return head_->data;
  }

  template< typename T >
  T& List< T >::back() noexcept
  {
    return tail_->data;
  }

  template< typename T >
  const T& List< T >::back() const noexcept
  {
    return tail_->data;
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    Node< T >* newnode = new Node< T >{data, nullptr, tail};
    if (!tail_)
    {
      head_ = newnode;
    }
    else
    {
      tail_->next = newnode;
    }
    tail_ = newnode;
    size++;
  }

  template< typename T >
  void List< T >::push_back(T&& data)
  {
    Node< T >* newnode = new Node< T >{std::move(data), nullptr, tail};
    if (!tail_)
    {
      head_ = newnode;
    }
    else
    {
      tail_->next = newnode;
    }
    tail_ = newnode;
    size++;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    Node< T >* newnode = new Node< T >{data, nullptr, tail};
    if (!tail_)
    {
      head_ = newnode;
    }
    else
    {
      head_->prev = newnode;
    }
    head_ = newnode;
    size++;
  }

  template< typename T >
  void List< T >::push_front(T&& data)
  {
    Node< T >* newnode = new Node< T >{std::move(data), nullptr, tail};
    if (!tail_)
    {
      head_ = newnode;
    }
    else
    {
      head_->prev = newnode;
    }
    head_ = newnode;
    size++;
  }

  template< typename T >
  void List< T >::pop_back() noexcept
  {
    assert(!empty());
    Node< T >* newtail = tail_->prev;
    delete tail_;
    if (new_tail)
    {
      newtail->next = nullptr;
    }
    else
    {
      head_ = nullptr;
    }
    tail_ = newtail;
    size--;
  }

  template< typename T >
  void List< T >::pop_front() noexcept
  {
    assert(!empty());
    Node< T >* newhead = head_->next;
    delete head_;
    if (new_head)
    {
      newhead->prev = nullptr;
    }
    else
    {
      tail_ = nullptr;
    }
    head_ = newhead;
    size--;
  }

}
#endif
